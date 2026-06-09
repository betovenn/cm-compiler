%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "semantic.h"
#include "codegen.h"

extern int yylex();
extern int lineno;
extern FILE *yyin;
extern char *yytext;

void yyerror(const char *s);
static void set_syntax_context(const char *context);
static void clear_syntax_context(void);
static void write_summary(const char *input_file, int parse_result, int semantic_errors, int intermediate_generated, int intermediate_instructions);
static const char *friendly_token(const char *token);
static const char *syntax_message(const char *raw_message,const char *near_token);
static const char *syntax_suggestion(const char *raw_message,const char *near_token);
static void write_syntax_diagnostic(int line,const char *message,const char *near_token,const char *suggestion,int derived);

TreeNode *savedTree;

FILE *syntax_errors;
FILE *ast_file;
FILE *semantic_file;
FILE *summary_file;
FILE *code_file;

static const char *syntax_context = NULL;
static int syntax_error_count = 0;

%}

%define parse.error detailed
%define parse.lac full
%locations

%code requires {
    #include "ast.h"
}

%union {

    TreeNode *tree;
    char *string;
}

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%token IF ELSE INT VOID WHILE FOR RETURN

%token PLUS MINUS TIMES OVER
%token LT LE GT GE EQ NE
%token ASSIGN INC

%token SEMI COMMA

%token LPAREN RPAREN
%token LBRACKET RBRACKET
%token LBRACE RBRACE

%token <string> ID
%token <string> NUM

%type <tree> declaration declaration_list
%type <string> type_specifier
%type <tree> var_declaration fun_declaration
%type <tree> params param_list param
%type <tree> compound_stmt
%type <tree> statement_list
%type <tree> statement expression_stmt
%type <tree> selection_stmt iteration_stmt return_stmt
%type <tree> expression simple_expression additive_expression term factor
%type <tree> var call args arg_list
%type <tree> initialized_var_declaration for_init for_condition for_update increment_expression

%%

program
    : declaration_list
        {
            savedTree = $1;
        }
    ;

declaration_list
    : declaration_list declaration
        {
            TreeNode *t = $1;

            if(t != NULL) {

                while(t->sibling != NULL)
                    t = t->sibling;

                t->sibling = $2;

                $$ = $1;
            }
            else
                $$ = $2;
        }

    | declaration
        {
            $$ = $1;
        }
    ;

type_specifier
    : INT
        {
            $$ = "int";
        }

    | VOID
        {
            $$ = "void";
        }
    ;

declaration
    : var_declaration
    | fun_declaration
    ;

var_declaration
    : type_specifier ID SEMI
        {
            $$ = newDeclNode(VarDeclK);

            $$->attr = $2;
            $$->type = $1;
        }

    | type_specifier ID LBRACKET NUM RBRACKET SEMI
        {
            $$ = newDeclNode(VarDeclK);

            $$->attr = $2;
            $$->type = $1;
            $$->arraySize = $4;
            $$->isArray = 1;
        }
    ;

initialized_var_declaration
    : type_specifier ID ASSIGN expression
        {
            $$ = newDeclNode(VarDeclK);

            $$->attr = $2;
            $$->type = $1;
            $$->child[0] = $4;
        }
    ;

fun_declaration
    : type_specifier ID LPAREN params RPAREN compound_stmt
        {
            $$ = newDeclNode(FunDeclK);

            $$->attr = $2;
            $$->type = $1;

            $$->child[0] = $4;
            $$->child[1] = $6;
        }
    ;

params
    : param_list

    | VOID
        {
            $$ = NULL;
        }

    |
        {
            $$ = NULL;
        }
    ;

param_list
    : param_list COMMA param
        {
            TreeNode *t = $1;

            while(t->sibling != NULL)
                t = t->sibling;

            t->sibling = $3;

            $$ = $1;
        }

    | param
        {
            $$ = $1;
        }
    ;

param
    : type_specifier ID
        {
            $$ = newDeclNode(ParamK);

            $$->attr = $2;
            $$->type = $1;
        }

    | type_specifier ID LBRACKET RBRACKET
        {
            $$ = newDeclNode(ParamK);

            $$->attr = $2;
            $$->type = $1;
            $$->isArray = 1;
        }
    ;

compound_stmt
    : LBRACE statement_list RBRACE
        {
            $$ = newStmtNode(CompoundK);

            $$->child[1] = $2;
        }
    ;

statement_list
    : statement_list statement
        {
            TreeNode *t = $1;

            if(t == NULL)
                $$ = $2;

            else {

                while(t->sibling != NULL)
                    t = t->sibling;

                t->sibling = $2;

                $$ = $1;
            }
        }

    |
        {
            $$ = NULL;
        }
    ;

statement
    : expression_stmt

    | var_declaration

    | initialized_var_declaration SEMI
        {
            $$ = $1;
        }

    | compound_stmt

    | selection_stmt

    | iteration_stmt

    | return_stmt

    | error SEMI
        {
            yyerrok;
            $$ = NULL;
        }
    ;

expression_stmt
    : expression SEMI
        {
            $$ = $1;
        }

    | increment_expression SEMI
        {
            $$ = $1;
        }

    | SEMI
        {
            $$ = NULL;
        }
    ;

selection_stmt
    : IF LPAREN if_condition_context expression RPAREN clear_condition_context statement %prec LOWER_THAN_ELSE
        {
            $$ = newStmtNode(IfK);

            $$->child[0] = $4;
            $$->child[1] = $7;
        }

    | IF LPAREN if_condition_context expression RPAREN clear_condition_context statement ELSE statement
        {
            $$ = newStmtNode(IfK);

            $$->child[0] = $4;
            $$->child[1] = $7;
            $$->child[2] = $9;
        }

    | IF LPAREN if_condition_context error RPAREN clear_condition_context statement %prec LOWER_THAN_ELSE
        {
            yyerrok;

            $$ = newStmtNode(IfK);
            $$->child[1] = $7;
        }

    | IF LPAREN if_condition_context error RPAREN clear_condition_context statement ELSE statement
        {
            yyerrok;

            $$ = newStmtNode(IfK);
            $$->child[1] = $7;
            $$->child[2] = $9;
        }
    ;

iteration_stmt
    : WHILE LPAREN while_condition_context expression RPAREN clear_condition_context statement
        {
            $$ = newStmtNode(WhileK);

            $$->child[0] = $4;
            $$->child[1] = $7;
        }

    | WHILE LPAREN while_condition_context error RPAREN clear_condition_context statement
        {
            yyerrok;

            $$ = newStmtNode(WhileK);
            $$->child[1] = $7;
        }

    | FOR LPAREN for_init SEMI for_condition SEMI for_update RPAREN statement
        {
            $$ = newStmtNode(ForK);

            $$->child[0] = $3;
            $$->child[1] = $5;
            $$->child[2] = $7;
            $$->child[3] = $9;
        }
    ;

for_init
    : expression
        {
            $$ = $1;
        }

    | increment_expression
        {
            $$ = $1;
        }

    | initialized_var_declaration
        {
            $$ = $1;
        }

    | type_specifier ID
        {
            $$ = newDeclNode(VarDeclK);

            $$->attr = $2;
            $$->type = $1;
        }

    |
        {
            $$ = NULL;
        }
    ;

for_condition
    : expression
        {
            $$ = $1;
        }

    |
        {
            $$ = NULL;
        }
    ;

for_update
    : expression
        {
            $$ = $1;
        }

    | increment_expression
        {
            $$ = $1;
        }

    |
        {
            $$ = NULL;
        }
    ;

if_condition_context
    :
        {
            set_syntax_context("en la condicion del if");
        }
    ;

while_condition_context
    :
        {
            set_syntax_context("en la condicion del while");
        }
    ;

clear_condition_context
    :
        {
            clear_syntax_context();
        }
    ;

return_stmt
    : RETURN SEMI
        {
            $$ = newStmtNode(ReturnK);
        }

    | RETURN expression SEMI
        {
            $$ = newStmtNode(ReturnK);

            $$->child[0] = $2;
        }
    ;

expression
    : var ASSIGN expression
        {
            $$ = newStmtNode(AssignK);

            $$->child[0] = $1;
            $$->child[1] = $3;
        }

    | simple_expression
    ;

increment_expression
    : var INC
        {
            TreeNode *one = newExpNode(ConstK);
            TreeNode *op = newExpNode(OpK);
            TreeNode *left = newExpNode(IdK);

            one->attr = "1";

            left->attr = $1->attr;
            left->isArray = $1->isArray;
            left->child[0] = $1->child[0];

            op->attr = "+";
            op->child[0] = left;
            op->child[1] = one;

            $$ = newStmtNode(AssignK);
            $$->child[0] = $1;
            $$->child[1] = op;
        }
    ;

simple_expression
    : additive_expression LT additive_expression
        {
            $$ = newExpNode(OpK);

            $$->attr = "<";

            $$->child[0] = $1;
            $$->child[1] = $3;
        }

    | additive_expression LE additive_expression
        {
            $$ = newExpNode(OpK);

            $$->attr = "<=";

            $$->child[0] = $1;
            $$->child[1] = $3;
        }

    | additive_expression GT additive_expression
        {
            $$ = newExpNode(OpK);

            $$->attr = ">";

            $$->child[0] = $1;
            $$->child[1] = $3;
        }

    | additive_expression GE additive_expression
        {
            $$ = newExpNode(OpK);

            $$->attr = ">=";

            $$->child[0] = $1;
            $$->child[1] = $3;
        }

    | additive_expression EQ additive_expression
        {
            $$ = newExpNode(OpK);

            $$->attr = "==";

            $$->child[0] = $1;
            $$->child[1] = $3;
        }

    | additive_expression NE additive_expression
        {
            $$ = newExpNode(OpK);

            $$->attr = "!=";

            $$->child[0] = $1;
            $$->child[1] = $3;
        }

    | additive_expression
        {
            $$ = $1;
        }
    ;

additive_expression
    : additive_expression PLUS term
        {
            $$ = newExpNode(OpK);

            $$->attr = "+";

            $$->child[0] = $1;
            $$->child[1] = $3;
        }

    | additive_expression MINUS term
        {
            $$ = newExpNode(OpK);

            $$->attr = "-";

            $$->child[0] = $1;
            $$->child[1] = $3;
        }

    | term
        {
            $$ = $1;
        }
    ;

term
    : term TIMES factor
        {
            $$ = newExpNode(OpK);

            $$->attr = "*";

            $$->child[0] = $1;
            $$->child[1] = $3;
        }

    | term OVER factor
        {
            $$ = newExpNode(OpK);

            $$->attr = "/";

            $$->child[0] = $1;
            $$->child[1] = $3;
        }

    | factor
        {
            $$ = $1;
        }
    ;

factor
    : LPAREN expression RPAREN
        {
            $$ = $2;
        }

    | var

    | call

    | NUM
        {
            $$ = newExpNode(ConstK);

            $$->attr = $1;
        }
    ;

var
    : ID
        {
            $$ = newExpNode(IdK);

            $$->attr = $1;
        }

    | ID LBRACKET expression RBRACKET
        {
            $$ = newExpNode(IdK);

            $$->attr = $1;
            $$->child[0] = $3;
            $$->isArray = 1;
        }
    ;

call
    : ID LPAREN args RPAREN
        {
            $$ = newExpNode(CallK);

            $$->attr = $1;

            $$->child[0] = $3;
        }
    ;

args
    : arg_list

    |
        {
            $$ = NULL;
        }
    ;

arg_list
    : arg_list COMMA expression
        {
            TreeNode *t = $1;

            while(t->sibling != NULL)
                t = t->sibling;

            t->sibling = $3;

            $$ = $1;
        }

    | expression
        {
            $$ = $1;
        }
    ;

%%

static void set_syntax_context(const char *context) {

    syntax_context = context;
}

static void clear_syntax_context(void) {

    syntax_context = NULL;
}

void yyerror(const char *s) {

    extern int lex_error_count;
    int line = yylloc.first_line > 0 ? yylloc.first_line : lineno;
    const char *near_token = yytext != NULL ? yytext : "";
    const char *message = syntax_message(s,near_token);
    const char *suggestion = syntax_suggestion(s,near_token);
    syntax_error_count++;

    write_syntax_diagnostic(line,message,near_token,suggestion,lex_error_count > 0);
}

static const char *friendly_token(const char *token) {

    if(token == NULL)
        return "";
    if(strcmp(token,"RPAREN") == 0)
        return "')'";
    if(strcmp(token,"LPAREN") == 0)
        return "'('";
    if(strcmp(token,"SEMI") == 0)
        return "';'";
    if(strcmp(token,"COMMA") == 0)
        return "','";
    if(strcmp(token,"LBRACKET") == 0)
        return "'['";
    if(strcmp(token,"RBRACKET") == 0)
        return "']'";
    if(strcmp(token,"LBRACE") == 0)
        return "'{'";
    if(strcmp(token,"RBRACE") == 0)
        return "'}'";
    if(strcmp(token,"ID") == 0)
        return "identificador";
    if(strcmp(token,"NUM") == 0)
        return "numero";
    if(strcmp(token,"INT") == 0)
        return "'int'";
    if(strcmp(token,"VOID") == 0)
        return "'void'";
    if(strcmp(token,"FOR") == 0)
        return "'for'";
    if(strcmp(token,"ASSIGN") == 0)
        return "'='";
    if(strcmp(token,"PLUS") == 0)
        return "'+'";
    if(strcmp(token,"INC") == 0)
        return "'++'";
    if(strcmp(token,"end of file") == 0)
        return "fin de archivo";

    return token;
}

static const char *syntax_message(const char *raw_message,const char *near_token) {

    if(raw_message != NULL && strstr(raw_message,"unexpected end of file") != NULL)
        return "Fin de archivo inesperado.";
    if(near_token != NULL && strcmp(near_token,")") == 0 &&
       raw_message != NULL && strstr(raw_message,"expecting INT or VOID") != NULL)
        return "Lista de parametros invalida en declaracion de funcion.";
    if(near_token != NULL && strcmp(near_token,"=") == 0)
        return "Declaracion invalida en esta posicion.";
    if(near_token != NULL && strcmp(near_token,"+") == 0)
        return "Expresion incompleta o operador '+' fuera de lugar.";
    if(near_token != NULL && strcmp(near_token,"}") == 0)
        return "Bloque cerrado antes de completar la sentencia anterior.";
    if(raw_message != NULL && strstr(raw_message,"expecting SEMI or LBRACKET") != NULL)
        return "Declaracion de variable incompleta.";
    if(raw_message != NULL && strstr(raw_message,"unexpected ID") != NULL)
        return "Token inesperado en esta posicion.";

    return "Token inesperado durante el analisis sintactico.";
}

static const char *syntax_suggestion(const char *raw_message,const char *near_token) {

    if(raw_message != NULL && strstr(raw_message,"unexpected end of file") != NULL)
        return "Revise si falta cerrar '}', ')' o completar una sentencia antes del fin de archivo.";
    if(near_token != NULL && strcmp(near_token,")") == 0 &&
       raw_message != NULL && strstr(raw_message,"expecting INT or VOID") != NULL)
        return "Use una lista de parametros valida o dejela vacia, por ejemplo int main().";
    if(near_token != NULL && strcmp(near_token,"=") == 0)
        return "Revise si la inicializacion pertenece a una declaracion local o a la inicializacion de un for.";
    if(near_token != NULL && strcmp(near_token,"+") == 0)
        return "Complete ambos operandos del operador o use incremento como i++.";
    if(near_token != NULL && strcmp(near_token,"}") == 0)
        return "Revise si falta una sentencia despues de if/while o si falta ';'.";
    if(raw_message != NULL && strstr(raw_message,"expecting SEMI or LBRACKET") != NULL)
        return "Termine la declaracion con ';' o declare un arreglo con '[NUM]'.";

    return "Compare la linea con la gramatica de C- y revise el token indicado.";
}

static void write_syntax_diagnostic(int line,const char *message,const char *near_token,const char *suggestion,int derived) {

    fprintf(syntax_errors,"[Sintactico][Linea %-4d] %s\n",line,message);
    if(syntax_context != NULL)
        fprintf(syntax_errors,"Contexto: %s\n",syntax_context);
    if(near_token != NULL && strlen(near_token) > 0)
        fprintf(syntax_errors,"Cerca de: '%s'\n",near_token);
    if(suggestion != NULL && strlen(suggestion) > 0)
        fprintf(syntax_errors,"Sugerencia: %s\n",suggestion);
    if(derived)
        fprintf(syntax_errors,"Nota: este error puede ser derivado de errores lexicos previos.\n");
    fprintf(syntax_errors,"\n");
}

static void write_summary(const char *input_file, int parse_result, int semantic_errors, int intermediate_generated, int intermediate_instructions) {

    extern int lex_error_count;
    extern int token_count;
    const char *first_error_stage = "ninguna";

    fprintf(summary_file,"=== RESUMEN DE COMPILACION ===\n");
    fprintf(summary_file,"Entrada: %s\n\n",input_file != NULL ? input_file : "stdin");

    if(lex_error_count > 0)
        first_error_stage = "Lexico";
    else if(syntax_error_count > 0 || parse_result != 0)
        first_error_stage = "Sintactico";
    else if(semantic_errors > 0)
        first_error_stage = "Semantico";

    fprintf(summary_file,"Etapa        Estado        Detalle\n");
    fprintf(summary_file,"-----------------------------------------------\n");
    fprintf(summary_file,"Lexico       %-12s %d error(es), %d token(s)\n",
            lex_error_count == 0 ? "correcto" : "con errores",
            lex_error_count,
            token_count);
    fprintf(summary_file,"Sintactico   %-12s %d error(es)\n",
            syntax_error_count == 0 && parse_result == 0 ? "correcto" : "con errores",
            syntax_error_count);
    if(lex_error_count > 0 && syntax_error_count > 0)
        fprintf(summary_file,"              %-12s errores sintacticos posiblemente derivados del lexico\n","");

    if(lex_error_count > 0 || syntax_error_count > 0 || parse_result != 0 || savedTree == NULL) {
        fprintf(summary_file,"AST          %-12s revise output/LexErr.txt y output/SintaxErr.txt\n","no generado");
        fprintf(summary_file,"Semantico    %-12s requiere AST valido\n","omitido");
        fprintf(summary_file,"Intermedio   %-12s requiere AST valido\n","omitido");
    }
    else {
        fprintf(summary_file,"AST          %-12s output/Arbol.txt\n","generado");
        fprintf(summary_file,"Semantico    %-12s %d error(es)\n",
                semantic_errors == 0 ? "correcto" : "con errores",
                semantic_errors);
        fprintf(summary_file,"Intermedio   %-12s %s\n",
                intermediate_generated ? "generado" : "omitido",
                intermediate_generated ? "output/CodigoIntermedio.txt" : "requiere semantica correcta");
        if(intermediate_generated)
            fprintf(summary_file,"              %-12s %d instruccion(es)\n","",intermediate_instructions);
    }

    fprintf(summary_file,"\nPrimer error real: %s\n",first_error_stage);
    if(lex_error_count > 0)
        fprintf(summary_file,"Gestion: AST, semantico e intermedio omitidos por errores lexicos.\n");
    else if(syntax_error_count > 0 || parse_result != 0)
        fprintf(summary_file,"Gestion: AST, semantico e intermedio omitidos por errores sintacticos.\n");
    else if(semantic_errors > 0)
        fprintf(summary_file,"Gestion: codigo intermedio omitido por errores semanticos.\n");
    else
        fprintf(summary_file,"Gestion: todas las etapas completadas.\n");

    fprintf(summary_file,"\nArchivos generados:\n");
    fprintf(summary_file,"- Tokens:     output/tokens.txt\n");
    fprintf(summary_file,"- Lexico:     output/LexErr.txt\n");
    fprintf(summary_file,"- Sintactico: output/SintaxErr.txt\n");
    fprintf(summary_file,"- AST:        output/Arbol.txt\n");
    fprintf(summary_file,"- Semantico:  output/Semantic.txt\n");
    fprintf(summary_file,"- Intermedio: output/CodigoIntermedio.txt\n");
}

int main(int argc,char *argv[]) {

    extern FILE *tokens_file;
    extern FILE *lex_errors;
    extern int lex_error_count;
    extern void finishTokenOutput(void);
    int parse_result;
    int semantic_errors = 0;
    int intermediate_generated = 0;
    int intermediate_instructions = 0;
    const char *input_file = argc > 1 ? argv[1] : NULL;

    tokens_file = fopen("output/tokens.txt","w");
    lex_errors = fopen("output/LexErr.txt","w");

    syntax_errors = fopen("output/SintaxErr.txt","w");

    ast_file = fopen("output/Arbol.txt","w");
    semantic_file = fopen("output/Semantic.txt","w");
    summary_file = fopen("output/Resumen.txt","w");
    code_file = fopen("output/CodigoIntermedio.txt","w");

    fprintf(tokens_file,"=== TOKENS POR LINEA ===\n\n");
    fprintf(lex_errors,"=== ANALISIS LEXICO ===\n\n");
    fprintf(syntax_errors,"=== ANALISIS SINTACTICO ===\n\n");

    if(argc > 1) {

        yyin = fopen(argv[1],"r");

        if(!yyin) {

            printf("No se pudo abrir archivo\n");

            return 1;
        }
    }

    parse_result = yyparse();

    finishTokenOutput();

    if(lex_error_count == 0)
        fprintf(lex_errors,"No se encontraron errores lexicos.\n");

    fprintf(lex_errors,"\nTotal de errores lexicos: %d\n",lex_error_count);

    if(syntax_error_count == 0)
        fprintf(syntax_errors,"No se encontraron errores sintacticos.\n");

    fprintf(syntax_errors,"\nTotal de errores sintacticos: %d\n",syntax_error_count);

    fprintf(ast_file,"=== ARBOL SINTACTICO ABSTRACTO ===\n\n");

    if(lex_error_count > 0 || syntax_error_count > 0 || parse_result != 0 || savedTree == NULL) {
        fprintf(ast_file,"Estado: no generado\n\n");
        fprintf(ast_file,"No se genero el AST porque existen errores lexicos o sintacticos.\n");

        fprintf(semantic_file,"=== ANALISIS SEMANTICO ===\n\n");
        fprintf(semantic_file,"Estado: omitido\n\n");
        fprintf(semantic_file,"No se ejecuto el analisis semantico porque no existe un AST valido.\n");
        fprintf(semantic_file,"Revise output/LexErr.txt y output/SintaxErr.txt.\n");

        fprintf(code_file,"=== CODIGO INTERMEDIO ===\n\n");
        fprintf(code_file,"Estado: omitido\n\n");
        fprintf(code_file,"Codigo intermedio omitido por errores previos.\n");
    }
    else {
        fprintf(ast_file,"Estado: generado\n\n");
        printTree(savedTree,0,ast_file);
        semantic_errors = semanticAnalyze(savedTree,semantic_file);

        if(semantic_errors == 0) {
            intermediate_instructions = generateIntermediateCode(savedTree,code_file);
            intermediate_generated = 1;
        }
        else {
            fprintf(code_file,"=== CODIGO INTERMEDIO ===\n\n");
            fprintf(code_file,"Estado: omitido\n\n");
            fprintf(code_file,"Codigo intermedio omitido por errores previos.\n");
            fprintf(code_file,"Revise output/Semantic.txt.\n");
        }
    }

    write_summary(input_file, parse_result, semantic_errors, intermediate_generated, intermediate_instructions);

    fclose(tokens_file);
    fclose(lex_errors);
    fclose(syntax_errors);
    fclose(ast_file);
    fclose(semantic_file);
    fclose(summary_file);
    fclose(code_file);

    return 0;
}
