%{
    void yerror (char *s);
    int yylex();

    extern int yylineno;

    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include "symboltable.h"
    #include "utility.h"

    symvartype symboltable[MAX_VARIABLES];  
%}

%start entrypoint

%union {
    char character;
    int integer;
    double decimal;
    char * string;
}

%token IF ELSE_IF ELSE REPEAT WHILE UNTIL
%token SET TO_BE AS
%token DO THANK_YOU
%token EXECUTE FUNCTION RECEIVING RETURNING RETURN
%token COMMA SEMICOLON
%token INT STR DOUBLE
%token EQ GT GE LT LE NE
%token NUMBER_LITERAL STRING_LITERAL
%token VAR
%token ADD SUBSTRACT PROD DIV MODULE
%token AND OR NOT
%token OPEN_B CLOSE_B OPEN_P CLOSE_P
%token PRINT
%token START END
%token DEFINE PASSING


%type<string> statement
/*
%type<string> block
%type<string> while
%type<string> command
%type<string> ifclause
%type<string> elsetrain
*/
%type<string> expression
/*
%type<string> asigned
%type<string> assignment
%type<string> vardeclaration
%type<string> fundeclaration
%type<string> fundefinition
%type<string> arglist
%type<string> arg
%type<string> funex
%type<string> returnstatement
%type<string> type
*/



%%

entrypoint: START statement END {;} 

statement:      expression {;}
        ;

expression: VAR EQ  VAR {;}
        |   VAR GT  VAR {;}
        |   VAR GE  VAR {;}
        |   VAR LT  VAR {;}
        |   VAR LE  VAR {;}
        |   VAR NE  VAR {;}
        |   VAR EQ  NUMBER_LITERAL {;}
        |   VAR GT  NUMBER_LITERAL {;}
        |   VAR GE  NUMBER_LITERAL {;}
        |   VAR LT  NUMBER_LITERAL {;}
        |   VAR LE  NUMBER_LITERAL {;}
        |   VAR NE  NUMBER_LITERAL {;}
        |   NUMBER_LITERAL EQ  VAR {;}
        |   NUMBER_LITERAL GT  VAR {;}
        |   NUMBER_LITERAL GE  VAR {;}
        |   NUMBER_LITERAL LT  VAR {;}
        |   NUMBER_LITERAL LE  VAR {;}
        |   NUMBER_LITERAL NE  VAR {;}
        ;