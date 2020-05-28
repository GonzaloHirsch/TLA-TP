%{
    void yerror (char *s);
    int yylex();

    extern int yylineno;


    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
%}

%start entryPoint

%union {
    character char;
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

command:    vardeclaration  SEMICOLON   {printf("Result %d\n", $1);}
        |   fundeclaration  SEMICOLON   {;}
        |   assignment      SEMICOLON   {;}

statement:  block       {;}
        |   while       {;}
        |   ifclause    {;}
    
block:  DO  statement THANK-YOU {;}
while:  REPEAT UNTIL    expression  statement   THANK-YOU   {;}
ifclause: IF    expression  statement
        |   IF  expression  statement   elsetrain
elsetrain:  ELSE-IF expression  statement   elsetrain
        |   ELSE    statement
