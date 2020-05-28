%{
    void yerror (char *s);
    int yylex();

    extern int yylineno;


    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
%}

%start entrypoint

%union {
    char character;
    int integer;
    double decimal;
    char * string;
}

%token IF ELSE-IF ELSE REPEAT WHILE
%token SET TO-BE AS
%token DO THANK-YOU
%token RECEIVING RETURN
%token COMMA SEMICOLON
%token INT STR DOUBLE
%token EQ GT GE LT LE NE

%%

entrypoint: 

command:    vardeclaration  SEMICOLON   {printf("Result %d\n", $1);}
        |   fundeclaration    {;}
        |   assignment      SEMICOLON   {;}


statement:  block       {;}
        |   while       {;}
        |   ifclause    {;}
        |   command statement   {;}
        |   command
    
block:  DO  statement THANK-YOU {;}

while:  REPEAT UNTIL    expression  statement   THANK-YOU   {;}

ifclause: IF    expression  statement
        |   IF  expression  statement   elsetrain

elsetrain:  ELSE-IF expression  statement   elsetrain
        |   ELSE    statement


expression: VAR EQ  VAR
        |   VAR GT  VAR
        |   VAR GE  VAR
        |   VAR LT  VAR
        |   VAR LE  VAR
        |   VAR NE  VAR
        |   STR-LITERAL
        |   NUMBER-LITERAL


assignment: SET VAR TO-BE   expression

vardeclaration: SET VAR AS  type

fundeclaration: SET VAR RECEIVING   arglist AS  type

fundefinition:  DEFINE  VAR RECEIVING   arglist AS  statement

type:   INT
    |   STR
    |   DOUBLE