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
    char string[240];
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


%type<string> hyperstatement
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

entrypoint: START hyperstatements END {printf("Entry point, should have start, statement, end\n");}
        |       START END       {;}
        ;

hyperstatements: hyperstatement hyperstatements {;}
        |       hyperstatement {;}
        ;

hyperstatement:
                statement SEMICOLON {printf("Just reading a statement\n");}
        |        block   {;}
        |        ifsentence        {;}
        |       while   {;}
        ;

ifsentence:
                IF OPEN_P expression CLOSE_P block   {printf("ifff \n");}
        |       IF OPEN_P expression CLOSE_P block elsetrain {printf("if that has elsetrain\n");}
        ;

elsetrain:
                ELSE block {printf("last else\n");}
        |       ELSE_IF OPEN_P expression CLOSE_P block {printf("else if\n");}
        |       ELSE_IF OPEN_P expression CLOSE_P  block elsetrain {printf("else if with else train\n");}
        ;

while:  
        WHILE OPEN_P expression CLOSE_P block {printf("while shit\n");}
        ;

statement:
                expression      {;}
        ;

block:  OPEN_B hyperstatements  CLOSE_B {printf("In a block\n");}
        ;
expression: VAR EQ  VAR {printf("var equals var!\n");}
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
