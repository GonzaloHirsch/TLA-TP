%{
#include "y.tab.h"
%}

integer     [0-9]+
number		-?[0-9]+(\.[0-9]+)?
string		\"[^\"]*\"
varName		[a-zA-Z][a-zA-Z0-9]*

%%
"if"			return IF;
"else if"       return ELSE_IF;
"else"          return ELSE; 
"while"         return WHILE;
","             return COMMA;
";"            	return SEMICOLON;
"."             return DOT;
"int"           return INT;
"int[]"         return INT_ARR;
"str"           return STR;
"double"        return DOUBLE;
"double[]"      return DOUBLE_ARR;
"forEach"       return FOREACH;
"->"            return RIGHT_ARROW;
"="             return ASSIGN_EQ;
"=="            return EQ;
">"             return GT;
">="            return GE;
"<"            	return LT;
"<="            return LE;
"!="            return NE;
"+"             return ADD;
"-"             return SUBS;
"*."            return SPROD;
"*"             return PROD;
"/"             return DIV;
"&&"            return AND;
"||"            return OR;
"!"             return NOT;
"{"             return OPEN_B;
"}"             return CLOSE_B;
"("             return OPEN_P;
")"             return CLOSE_P;
"["             return OPEN_BRACK;
"]"             return CLOSE_BRACK;
"print"         return PRINT;
"start"         return START;
"end"           return END;
"*x"            return CROSS;
"getInt"        return GET_INT;
"getDouble"     return GET_DOUBLE;
"getString"     return GET_STRING;
"exit()"        return EXIT;
[\t ]           ;
\n              {yylineno++;}
{number} 		{strcpy(yylval.string, yytext);return NUMBER_LITERAL;}
{string}        {strcpy(yylval.string, yytext);return STRING_LITERAL;}
{varName} 		{strcpy(yylval.string, yytext);return VAR;}
.               ;

%%

int yywrap (void) {
    return 1;
}