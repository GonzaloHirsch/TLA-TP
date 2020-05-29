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

statement:  block   statement   {;}
        |   while   statement   {;}
        |   ifclause    statement  {;}
        |   command statement  {;}
        |   block {;}
        |   while {;}
        |   ifclause {;}
        ;
block:  DO  statement THANK_YOU {;}
        ;
while:  REPEAT UNTIL    expression  statement   THANK_YOU   {;}
        ;
ifclause: IF    expression  statement   {;}
        |   IF  expression  statement   elsetrain {;}
        ;
elsetrain:  ELSE_IF expression  statement   elsetrain {;}
        |   ELSE    statement {;}
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

asigned:    STRING_LITERAL {;}
        |   NUMBER_LITERAL {;} 
        ;

assignment: SET VAR TO_BE asigned {;}
        ;
vardeclaration: SET VAR AS type {;}
        ;
fundeclaration: SET FUNCTION VAR RECEIVING   arglistdecl RETURNING  type {;}
        ;
fundefinition:  DEFINE FUNCTION VAR RECEIVING   arglistdecl AS  statement returnstatement{;}
        ;
arglist:    arglist COMMA arg {;}
        |   arg COMMA   {;}
        ;
arg:    type    VAR
        ;

funex:  EXECUTE FUNCTION    VAR PASSING arglist {;}
        ;

        
returnstatement:    RETURN  expression  {char * str = (char *)malloc((strlen("return") + 1) sizeof(char)); strcpy(str, "return"); $$ = c_string(2, str, $2);}
        ;

type:   INT     {char * str = (char *)malloc((strlen("int") + 1) sizeof(char)); strcpy(str, "int"); $$ = str;}
    |   STR     {char * str = (char *)malloc((strlen("char *") + 1) sizeof(char)); strcpy(str, "char *"); $$ = str;}
    |   DOUBLE  {char * str = (char *)malloc((strlen("double") + 1) sizeof(char)); strcpy(str, "double"); $$ = str;}
    ;