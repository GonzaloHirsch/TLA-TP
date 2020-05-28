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

command:    varDeclaration  SEMICOLON   {printf("Result %d\n", $1);}
        |   funDeclaration  SEMICOLON   {;}
        |   assignment      SEMICOLON   {;}

statement:  block   {;}
            while   {;}
            ifClause    {;}
    
block:  DO  statement   