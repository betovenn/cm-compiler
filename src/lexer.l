%{
#include <stdio.h>
%}

KEYWORD (if|else|void|int|while|break|switch|default|case|return|endif)
NUM     [0-9]*
ID      [A-Za-z][A-Za-z0-9]*
SYMBOL  [;:,\[\](){}+\-*/=<>|]

%%

{KEYWORD} {
    printf("KEYWORD: %s\n", yytext);
}

{NUM} {
    printf("NUM: %s\n", yytext);
}

{ID} {
    printf("ID: %s\n", yytext);
}

{SYMBOL} {
    printf("SYMBOL: %s\n", yytext);
}

"{"[^{}\n]*"}"     /* eat up one-line comments */
[ \t\n\r\v\f]+          /* eat up whitespace */

%%

int main( int argc, char **argv ) {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;
    yylex();

    return 0;
}

int yywrap(void) {
    return 1;
}
