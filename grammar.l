%{
#include "y.tab.h"
%}

integer     [0-9]+
number		-?[0-9]+(\.[0-9]+)?
string		\"[^\"]*\"
varName		[a-zA-Z][a-zA-Z0-9]*

%%

"until"         return UNTIL;
"execute"       return EXECUTE;
"if"			return IF;
"else if"       return ELSE_IF;
"else"          return ELSE; 
"repeat"        return REPEAT;
"while"         return WHILE;
"set"           return SET;
"to be"         return TO_BE;
"as"            return AS;
"equal"         return EQ;
"do"            return DO;
"function"      return FUNCTION;
"returning"     return RETURNING;
"return"        return RETURN;
","             return COMMA;
";"            	return SEMICOLON;
"."             return DOT;
"int"           return INT;
"str"           return STR;
"double"        return DOUBLE;
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
"-"             return SUBSTRACT;
"*"             return PROD;
"/"             return DIV;
"%"             return MODULE;
"&&"            return AND;
"||"             return OR;
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