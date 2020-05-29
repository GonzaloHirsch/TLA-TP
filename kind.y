%{
    void yerror (char *s);
    int yylex();

    extern int yylineno;


    symvartype symboltable[MAX_VARIABLES];  
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include "symboltable.h"
    #include "utility.h"
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
%token BEGIN END
%token DEFINE PASSING


%type<string> statement
%type<string> block
%type<string> while
%type<string> command
%type<string> ifclause
%type<string> elsetrain
%type<string> expression
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




%%

entrypoint: BEGIN statement END {;} 
        ;       

command:    vardeclaration  SEMICOLON   {printf("Result %d\n", $1);}
        |   fundeclaration  SEMICOLON  {;}
        |   assignment      SEMICOLON   {;}
        |   funex   SEMICOLON   {;}
        ;

statement:  block   statement SEMICOLON  {;}
        |   while   statement SEMICOLON  {;}
        |   ifclause    statement SEMICOLON {;}
        |   command statement SEMICOLON {;}
        |   block SEMICOLON {;}
        |   while SEMICOLON {;}
        |   ifclause SEMICOLON {;}
        ;
block:  DO  statement THANK_YOU SEMICOLON {;}
        ;
while:  REPEAT UNTIL    expression  statement   THANK_YOU  SEMICOLON  {;}
        ;
ifclause: IF    expression  statement SEMICOLON  {;}
        |   IF  expression  statement   elsetrain SEMICOLON {;}
        ;
elsetrain:  ELSE_IF expression  statement   elsetrain SEMICOLON {;}
        |   ELSE    statement SEMICOLON {;}
        ;

expression: VAR EQ  VAR SEMICOLON {;}
        |   VAR GT  VAR SEMICOLON {;}
        |   VAR GE  VAR SEMICOLON {;}
        |   VAR LT  VAR SEMICOLON {;}
        |   VAR LE  VAR SEMICOLON {;}
        |   VAR NE  VAR SEMICOLON {;}
        |   VAR EQ  NUMBER_LITERAL SEMICOLON {;}
        |   VAR GT  NUMBER_LITERAL SEMICOLON {;}
        |   VAR GE  NUMBER_LITERAL SEMICOLON {;}
        |   VAR LT  NUMBER_LITERAL SEMICOLON {;}
        |   VAR LE  NUMBER_LITERAL SEMICOLON {;}
        |   VAR NE  NUMBER_LITERAL SEMICOLON {;}
        |   NUMBER_LITERAL EQ  VAR SEMICOLON {;}
        |   NUMBER_LITERAL GT  VAR SEMICOLON {;}
        |   NUMBER_LITERAL GE  VAR SEMICOLON {;}
        |   NUMBER_LITERAL LT  VAR SEMICOLON {;}
        |   NUMBER_LITERAL LE  VAR SEMICOLON {;}
        |   NUMBER_LITERAL NE  VAR SEMICOLON {;}
        ;

asigned:    STRING_LITERAL SEMICOLON {;}
        |   NUMBER_LITERAL SEMICOLON {;} 
        ;

assignment: SET VAR TO_BE asigned SEMICOLON {;}
        ;
vardeclaration: SET VAR AS type SEMICOLON {;}
        ;
fundeclaration: SET FUNCTION VAR RECEIVING   arglistdecl RETURNING  type SEMICOLON {;}
        ;
fundefinition:  DEFINE FUNCTION VAR RECEIVING   arglistdecl AS  statement returnstatement  {;}
        ;
arglist:    arglist COMMA arg SEMICOLON {;}
        |   arg COMMA SEMICOLON  {;}
        ;
arg:    type    VAR SEMICOLON {$$ = c_string(2, $1, $2)}
        ;

funex:  EXECUTE FUNCTION    VAR PASSING arglist SEMICOLON {;}
        ;


returnstatement:    RETURN  expression SEMICOLON {char * str = (char *)malloc((strlen("return") + 1) sizeof(char)); strcpy(str, "return"); $$ = c_string(2, str, $2);}
        ;

type:   INT     {char * str = (char *)malloc((strlen("int") + 1) sizeof(char)); strcpy(str, "int"); $$ = str;}
    |   STR     {char * str = (char *)malloc((strlen("char *") + 1) sizeof(char)); strcpy(str, "char *"); $$ = str;}
    |   DOUBLE  {char * str = (char *)malloc((strlen("double") + 1) sizeof(char)); strcpy(str, "double"); $$ = str;}
    ;