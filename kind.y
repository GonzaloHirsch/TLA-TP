%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include "symboltable.h"
    #include "utility.h"

    void yyerror (char *s);
    int yylex();
    
    extern int yylineno;

    symvartype symboltable[MAX_VARIABLES];  
%}

%start entrypoint

%union {
    char character;
    int integer;
    double decimal;
    char string[5000];
}

%token<string> IF ELSE_IF ELSE REPEAT WHILE UNTIL
%token<string> SET TO_BE AS
%token<string> DO THANK_YOU
%token<string> EXECUTE FUNCTION RECEIVING RETURNING RETURN
%token<string> COMMA SEMICOLON
%token<string> INT STR DOUBLE
%token<string> EQ GT GE LT LE NE
%token<string> NUMBER_LITERAL STRING_LITERAL
%token<string> VAR
%token<string> ADD SUBSTRACT PROD DIV MODULE
%token<string> AND OR NOT
%token<string> OPEN_B CLOSE_B OPEN_P CLOSE_P
%token<string> PRINT
%token<string> START END
%token<string> DEFINE PASSING

%type<string> hyperstatements
%type<string> hyperstatement
%type<string> entrypoint
%type<string> expression
%type<string> ifsentence
%type<string> statement
%type<string> block







%%

entrypoint: START hyperstatements END {printf("%s", c_string(3,"int main(){", $2, "return 1;}"));}
        |       START END       {printf("int main(){ return 1; }") ;}
        ;

hyperstatements: hyperstatement hyperstatements {;}
        |       hyperstatement {;}
        ;

hyperstatement:
                statement SEMICOLON {;}
        |        block   {;}
        |        ifsentence        {;}
        ;

ifsentence:
                IF      OPEN_P  expression      CLOSE_P block   {strcpy($$, c_string(5, $1, $2, $3, $4, $5)) ;}
        ;

statement:
                expression      {strcpy($$, $1);}
        ;

block:  OPEN_B hyperstatements  CLOSE_B {;}
        
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

%%

void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
	printf("-------------------------------------\nError: %s in line %d\n-------------------------------------\n", s, yylineno);
	exit(0);
}

int
main(void) {
        /*
	variables = malloc(MAX_VARIABLES * sizeof(VariableToken *));

	if (variables == NULL) {
		printf("Unable to allocate space for the variables\n");
		exit(EXIT_FAILURE);
	}
	memset(variables, '\0', sizeof(VariableToken *) * MAX_VARIABLES);
        */
	
	yyparse();

/*
	char * translation = translateToC((Token *)code);
	//We should always call get functions after translateToC
	char * functionsTranslation = getFunctions();
        */

/*
	if (translation == NULL) printf("Error allocating memory for generated C code.\n");
	else {
		printf("#include <stdio.h>\n");
		printf("#include <stdlib.h>\n\n");
		if(functionsTranslation != NULL) {
			printf("%s\n", functionsTranslation);
		}
		printf("int main(int argc, char const *argv[]) {\n");
		printf("%s\n", translation);
		printf("\nreturn 0;\n}");
	}

	if(translation != NULL) {
		free(translation);
	}
	if(functionsTranslation != NULL) {
		free(functionsTranslation);
	}
	freeFunctions();
	freeToken((Token *) code);
	freeVariables();
        */
	return 0;
}
