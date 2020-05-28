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

%%

entrypoint: 

command:    vardeclaration  SEMICOLON   {printf("Result %d\n", $1);}
        |   fundeclaration  SEMICOLON   {;}
        |   assignment      SEMICOLON   {;}

statement:  block       {;}
        |   while       {;}
        |   ifclause    {;}
        |   command statement   {;}
    
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

assignment: LET
