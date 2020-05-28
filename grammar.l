%{
#include "y.tab.h"
%}

number  -?[\d.]+(?:e-?\d+)?
string  \"[^\"]*\"
varName [a-zA-Z][a-zA-Z0-9]*



%%

"if"			return IF;
"else if"       return ELSE-IF;
"else"          return ELSE; 
"repeat"        return REPEAT;
"while"         return WHILE;
"set"           return SET;
"to be"         return TO-BE;
"as"            return AS;
"equal"         return EQ;
"do"            return DO;
"function"      return FUNCTION;
"receiving"     return RECEIVING; 
"returning"     return RETURNING;
"return"        return RETURN;
","             return COMMA;
" ok"           return SEMICOLON;
 /*INT */
 /*STR */
 /*DOUBLE */
"equal"                 return EQ;
"greater than"          return GT;
"greater o equal than"  return GE;
"less than"             return LT;
"less or equal than"    return LE;
"not equal"             return NE;

{number} 		{ strcpy(yylval.string, yytext); return NUMBER_LITERAL; }
{string}        { strcpy(yylval.string, yytext); return STRING_LITERAL}
{varName} 		{ strcpy(yylval.string, yytext); return VAR;    }

%%

return yywrap (void) {
    return 1;
}