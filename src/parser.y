%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"

extern int yylex();
extern int lineno;
extern FILE *yyin;
extern char *yytext;

void yyerror(const char *s);

TreeNode *savedTree;

FILE *syntax_errors;
FILE *ast_file;

%}

%define parse.error verbose

%code requires {
    #include "ast.h"
}

%union {

    TreeNode *tree;
    char *string;
}

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%token IF ELSE INT VOID WHILE RETURN

%token PLUS MINUS TIMES OVER
%token LT LE GT GE EQ NE
%token ASSIGN

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
%type <tree> local_declarations statement_list
%type <tree> statement expression_stmt
%type <tree> selection_stmt iteration_stmt return_stmt
%type <tree> expression simple_expression additive_expression term factor
%type <tree> var call args arg_list

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
    : INT ID
        {
            $$ = newDeclNode(ParamK);

            $$->attr = $2;
        }
    ;

compound_stmt
    : LBRACE local_declarations statement_list RBRACE
        {
            $$ = newStmtNode(CompoundK);

            $$->child[0] = $2;
            $$->child[1] = $3;
        }
    ;

local_declarations
    : local_declarations var_declaration
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

    | compound_stmt

    | selection_stmt

    | iteration_stmt

    | return_stmt

    | error SEMI
        {
            yyerror("Sentencia inválida");
            yyerrok;
            $$ = NULL;
        }
    ;

expression_stmt
    : expression SEMI
        {
            $$ = $1;
        }

    | SEMI
        {
            $$ = NULL;
        }
    ;

selection_stmt
    : IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
        {
            $$ = newStmtNode(IfK);

            $$->child[0] = $3;
            $$->child[1] = $5;
        }

    | IF LPAREN expression RPAREN statement ELSE statement
        {
            $$ = newStmtNode(IfK);

            $$->child[0] = $3;
            $$->child[1] = $5;
            $$->child[2] = $7;
        }
    ;

iteration_stmt
    : WHILE LPAREN expression RPAREN statement
        {
            $$ = newStmtNode(WhileK);

            $$->child[0] = $3;
            $$->child[1] = $5;
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

void yyerror(const char *s) {

    fprintf(
        syntax_errors,
        "Linea %d: %s cerca de '%s'\n",
        lineno,
        s,
        yytext
    );
}

int main(int argc,char *argv[]) {

    extern FILE *tokens_file;
    extern FILE *lex_errors;

    tokens_file = fopen("output/tokens.txt","w");
    lex_errors = fopen("output/LexErr.txt","w");

    syntax_errors = fopen("output/SintaxErr.txt","w");

    ast_file = fopen("output/Arbol.txt","w");

    if(argc > 1) {

        yyin = fopen(argv[1],"r");

        if(!yyin) {

            printf("No se pudo abrir archivo\n");

            return 1;
        }
    }

    yyparse();

    printTree(savedTree,0,ast_file);

    fclose(tokens_file);
    fclose(lex_errors);
    fclose(syntax_errors);
    fclose(ast_file);

    return 0;
}