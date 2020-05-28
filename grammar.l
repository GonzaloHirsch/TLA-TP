%{
#include "y.tab.h"
%}

number  -?[\d.]+(?:e-?\d+)?
varName [a-zA-Z][a-zA-Z0-9]*

"if"					return IF;

{number} 				{ strcpy(yylval.string, yytext); return NUMBER_LITERAL; }

%%