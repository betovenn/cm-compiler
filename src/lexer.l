%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../parser/parser.tab.h"

int lineno = 1;

FILE *tokens_file;
FILE *lex_errors;

void printToken(const char *type,const char *lexeme);
void printError(const char *lexeme,const char *msg);

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

                            printError(yytext,"Símbolo inválido");
                        }

%%

void printToken(const char *type,const char *lexeme) {

    fprintf(tokens_file,
            "(%s,%s)\n",
            type,
            lexeme);
}

void printError(const char *lexeme,const char *msg) {

    fprintf(lex_errors,
            "Linea %d: %s -> %s\n",
            lineno,
            lexeme,
            msg);
}

int yywrap() {

    return 1;
}
