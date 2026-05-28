%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../parser/parser.tab.h"

int lineno = 1;

FILE *tokens_file;
FILE *lex_errors;

int lex_error_count = 0;
int token_count = 0;

void printToken(const char *type,const char *lexeme);
void printError(const char *lexeme,const char *msg);
void finishTokenOutput(void);

static int current_token_line = 0;
static int tokens_in_current_line = 0;

#define YY_USER_ACTION \
    yylloc.first_line = lineno; \
    yylloc.last_line = lineno; \
    yylloc.first_column = 1; \
    yylloc.last_column = 1;

%}

%x COMMENT

DIGIT      [0-9]
LETTER     [A-Za-z]

ID         {LETTER}({LETTER}|{DIGIT})*
NUM        {DIGIT}+

%%

"/*"                    BEGIN(COMMENT);

<COMMENT>"*/"           BEGIN(INITIAL);

<COMMENT>\n             lineno++;

<COMMENT>.              ;

<COMMENT><<EOF>>        {
                            printError("/*","Comentario no cerrado");
                            return 0;
                        }

"//".*                  ;

[ \t\r]+                ;

\n                      lineno++;

"if"                    {
                            printToken("KEYWORD",yytext);
                            return IF;
                        }

"else"                  {
                            printToken("KEYWORD",yytext);
                            return ELSE;
                        }

"int"                   {
                            printToken("KEYWORD",yytext);
                            return INT;
                        }

"void"                  {
                            printToken("KEYWORD",yytext);
                            return VOID;
                        }

"while"                 {
                            printToken("KEYWORD",yytext);
                            return WHILE;
                        }

"return"                {
                            printToken("KEYWORD",yytext);
                            return RETURN;
                        }

"<="                    {
                            printToken("SYMBOL",yytext);
                            return LE;
                        }

"<"                     {
                            printToken("SYMBOL",yytext);
                            return LT;
                        }

">="                    {
                            printToken("SYMBOL",yytext);
                            return GE;
                        }

">"                     {
                            printToken("SYMBOL",yytext);
                            return GT;
                        }

"=="                    {
                            printToken("SYMBOL",yytext);
                            return EQ;
                        }

"!="                    {
                            printToken("SYMBOL",yytext);
                            return NE;
                        }

"="                     {
                            printToken("SYMBOL",yytext);
                            return ASSIGN;
                        }

"+"                     {
                            printToken("SYMBOL",yytext);
                            return PLUS;
                        }

"-"                     {
                            printToken("SYMBOL",yytext);
                            return MINUS;
                        }

"*"                     {
                            printToken("SYMBOL",yytext);
                            return TIMES;
                        }

"/"                     {
                            printToken("SYMBOL",yytext);
                            return OVER;
                        }

";"                     {
                            printToken("SYMBOL",yytext);
                            return SEMI;
                        }

","                     {
                            printToken("SYMBOL",yytext);
                            return COMMA;
                        }

"("                     {
                            printToken("SYMBOL",yytext);
                            return LPAREN;
                        }

")"                     {
                            printToken("SYMBOL",yytext);
                            return RPAREN;
                        }

"["                     {
                            printToken("SYMBOL",yytext);
                            return LBRACKET;
                        }

"]"                     {
                            printToken("SYMBOL",yytext);
                            return RBRACKET;
                        }

"{"                     {
                            printToken("SYMBOL",yytext);
                            return LBRACE;
                        }

"}"                     {
                            printToken("SYMBOL",yytext);
                            return RBRACE;
                        }

{NUM}                   {

                            yylval.string = strdup(yytext);

                            printToken("NUM",yytext);

                            return NUM;
                        }

{ID}                    {

                            yylval.string = strdup(yytext);

                            printToken("ID",yytext);

                            return ID;
                        }

.                       {

                            printError(yytext,"Simbolo invalido");
                        }

%%

void printToken(const char *type,const char *lexeme) {

    if(current_token_line != lineno) {

        if(tokens_in_current_line > 0)
            fprintf(tokens_file,"\n");

        fprintf(tokens_file,"Linea %-4d: ",lineno);

        current_token_line = lineno;
        tokens_in_current_line = 0;
    }

    fprintf(tokens_file,
            "%s%s(\"%s\")",
            tokens_in_current_line > 0 ? " " : "",
            type,
            lexeme);

    tokens_in_current_line++;
    token_count++;
}

void printError(const char *lexeme,const char *msg) {

    fprintf(lex_errors,
            "[Linea %-4d] %-10s -> %s\n",
            lineno,
            lexeme,
            msg);

    lex_error_count++;
}

void finishTokenOutput(void) {

    if(tokens_in_current_line > 0)
        fprintf(tokens_file,"\n");

    if(token_count == 0)
        fprintf(tokens_file,"No se leyeron tokens.\n");

    fprintf(tokens_file,"\nTotal de tokens: %d\n",token_count);
}

int yywrap() {

    return 1;
}
