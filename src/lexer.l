%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lineno = 1;
int last_token_line = -1;
int error_count = 0;

FILE *tokens_file;
FILE *errors_file;
FILE *symbols_file;

char sym_table[1000][100];
int sym_count = 0;

void add_symbol(const char* lex) {
    for(int i = 0; i < sym_count; i++) {
        if(strcmp(sym_table[i], lex) == 0) return;
    }
    strcpy(sym_table[sym_count++], lex);
}

void print_token(const char* type, const char* lexeme) {
    if (lineno != last_token_line) {
        if (last_token_line != -1) fprintf(tokens_file, "\n");
        fprintf(tokens_file, "%d.\t(%s, %s)", lineno, type, lexeme);
        last_token_line = lineno;
    } else {
        fprintf(tokens_file, " (%s, %s)", type, lexeme);
    }
}

void print_error(const char* lexeme, const char* msg) {
    char trunc_lex[12];
    if (strlen(lexeme) > 7) {
        strncpy(trunc_lex, lexeme, 7);
        trunc_lex[7] = '\0';
        strcat(trunc_lex, "...");
    } else {
        strcpy(trunc_lex, lexeme);
    }
    fprintf(errors_file, "%d.\t(%s, %s)\n", lineno, trunc_lex, msg);
    error_count++;
}
%}

%x MULTI_COMMENT

KEYWORD (if|else|void|int|while|break|switch|default|case|return|endif)
NUM     [0-9]+
ID      [A-Za-z][A-Za-z0-9]*
NUM_INV [0-9]+[A-Za-z]+

%%

"/*"                  { BEGIN(MULTI_COMMENT); }
<MULTI_COMMENT>"*/"   { BEGIN(INITIAL); }
<MULTI_COMMENT>\n     { lineno++; }
<MULTI_COMMENT><<EOF>> { print_error("/*", "Comentario no cerrado"); BEGIN(INITIAL); yyterminate(); }
<MULTI_COMMENT>.      { }

"//".* { }

"*/"                  { print_error(yytext, "Comentario no anidado"); }

{KEYWORD}             { print_token("KEYWORD", yytext); }

{NUM_INV}             { print_error(yytext, "Número inválido"); }

{NUM}                 { print_token("NUM", yytext); }

{ID}                  { 
                        add_symbol(yytext); 
                        print_token("ID", yytext); 
                      }

"=="|"<="|"<"|"+"|"-"|"*"|"/"|";"|","|"["|"]"|"("|")"|"{"|"}"|":="|"=" { 
                        print_token("SYMBOL", yytext); 
                      }

\n                    { lineno++; }

[ \t\r\v\f]+          { }

.                     { print_error(yytext, "Entrada no reconocida"); }

%%

int main(int argc, char **argv) {
    tokens_file = fopen("output/tokens.txt", "w");
    errors_file = fopen("output/Errores_lexicos.txt", "w");
    symbols_file = fopen("output/Tabla_simbolos.txt", "w");

    if (!tokens_file || !errors_file || !symbols_file) {
        printf("Error al crear archivos de salida.\n");
        return 1;
    }

    const char* keywords[] = {"if", "else", "void", "int", "while", "break", "switch", "default", "case", "return", "endif"};
    for(int i = 0; i < 11; i++) {
        add_symbol(keywords[i]);
    }

    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            printf("Error: No se encontró el archivo %s.\n", argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;
    }

    yylex();

    if (last_token_line != -1) {
        fprintf(tokens_file, "\n");
    }

    if (error_count == 0) {
        fprintf(errors_file, "No hay errores léxicos.\n");
    }

    for(int i = 0; i < sym_count; i++) {
        fprintf(symbols_file, "%d.\t%s\n", i + 1, sym_table[i]);
    }

    fclose(tokens_file);
    fclose(errors_file);
    fclose(symbols_file);
    if (yyin != stdin) fclose(yyin);

    return 0;
}

int yywrap(void) {
    return 1;
}
