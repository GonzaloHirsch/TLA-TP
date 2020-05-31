%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
    #include "symboltable.h"
    #include "utility.h"
    #include "node2.h"

    void yyerror (EntryPointNode ** node, char *s);
    int yylex();
    
    extern int yylineno;

    EntryPointNode * cstring;

    symvartype symboltable[MAX_VARIABLES];
%}

%start entrypoint


%union {
    char character;
    int integer;
    double decimal;
    char string[5000];
    struct GenericNode * node;
    struct NodeList * nodelist;
    struct EntryPointNode * entrypointnode;
}

%parse-param {struct EntryPointNode ** cstring}

%token<string> IF ELSE_IF ELSE REPEAT WHILE UNTIL
%token<string> SET TO_BE AS
%token<string> DO THANK_YOU
%token<string> EXECUTE FUNCTION RECEIVING RETURNING RETURN
%token<string> FOREACH RIGHT_ARROW
%token<string> COMMA SEMICOLON DOT
%token<string> INT STR DOUBLE
%token<string> INTEGER
%token<string> EQ GT GE LT LE NE
%token<string> NUMBER_LITERAL STRING_LITERAL
%token<string> VAR
%token<string> ADD SUBS PROD DIV MODULE CROSS
%token<string> AND OR NOT
%token<string> OPEN_B CLOSE_B OPEN_P CLOSE_P OPEN_BRACK CLOSE_BRACK
%token<string> PRINT
%token<string> START END
%token<string> DEFINE PASSING
%token<string> ASSIGN_EQ

%type<entrypointnode> entrypoint
%type<nodelist> hyperstatements
%type<node> hyperstatement
%type<string> expression
%type<string> generalexpression
%type<string> generaloperation
%type<string> operation
%type<string> unity
%type<string> expunity
%type<string> ifsentence
%type<string> statement
%type<string> block
%type<nodelist> inblockstatements
%type<string> inblockstatement
%type<string> funcall

%%

entrypoint: 	
        START hyperstatements END 	{
        printf("entrypoint\n");
        *cstring = newEntryPointNode($2); $$ = *cstring;
        strcpy((*cstring)->testString, "helloThere\n");
        // printf("%s", c_string("int main() {", $2, "return 1;}", "", ""));
        }
        |       START END       		{
                *cstring = newEntryPointNode(NULL); $$ = *cstring;
                strcpy((char * )(*cstring)->testString, "helloThere\n");
                }
        ;

hyperstatements: 	hyperstatement hyperstatements 	{$$ = addToNodeList($2, $1);}
        |       	hyperstatement 			{$$ = createNodeList($1);}
        ;

hyperstatement:	statement SEMICOLON 	{$$ = newGenericNode(NODE_HYPERSTATEMENT);}
        |       block   		{$$ = newGenericNode(NODE_HYPERSTATEMENT);}
        |       ifsentence        	{$$ = newGenericNode(NODE_HYPERSTATEMENT);}
        |      	while   		{$$ = newGenericNode(NODE_HYPERSTATEMENT);}
        |       function 		{$$ = newGenericNode(NODE_HYPERSTATEMENT);}
        ;

inblockstatements:	inblockstatement inblockstatements 	{;}
        | 		inblockstatement 			{;}
        ;
inblockstatement:	statement SEMICOLON 	{;}
        |       	ifsentence        	{;}
        |       	while   		{;}
        ;

ifsentence:	IF OPEN_P generalexpression CLOSE_P block   		{
        // strcpy($$, c_string("if (", $3, ")", $5, "")) ;
        ;
        }
        |       IF OPEN_P generalexpression CLOSE_P block elsetrain 	{printf("if that has elsetrain\n");}
        ;

elsetrain:	ELSE block 						{printf("last else\n");}
        |       ELSE_IF OPEN_P generalexpression CLOSE_P block 		{printf("else if\n");}
        |       ELSE_IF OPEN_P generalexpression CLOSE_P block elsetrain 	{printf("else if with else train\n");}
        ;

while:	WHILE OPEN_P generalexpression CLOSE_P block	{printf("while shit\n");}
        ;

statement:	generalexpression      {
        strcpy($$, $1);
        }
        |       assignment      {;}
        |       vardeclaration  {;}
        |       vardeclassignment {;}
        |       fundeclaration  {;}
        |       funcall         {;}
        |       foreach         {;}
        ;

vardeclaration:
        type VAR {;}
        | type  VAR OPEN_BRACK NUMBER_LITERAL CLOSE_BRACK {printf("declaring an array\n");}
        ;

vardeclassignment: type VAR ASSIGN_EQ generaloperation {;}
        | type VAR ASSIGN_EQ literal {;}
        | type VAR ASSIGN_EQ generalexpression {;}
        ;

foreach:
        VAR DOT FOREACH OPEN_P VAR RIGHT_ARROW foreachbody CLOSE_P {;}
        ; 
foreachbody:
        statement {;}
        | funblock {printf("funblock\n");}
        ;

block:	OPEN_B inblockstatements  CLOSE_B {
        // strcpy($$,c_string("{", $2, "}", "", ""));
                ;
        }
        ;

assignment:	VAR ASSIGN_EQ literal	        {;}
        |	VAR ASSIGN_EQ generaloperation 	{;} 
        |       VAR ASSIGN_EQ generalexpression {;}
        ;

literal:        STRING_LITERAL {;}
        ;

arrayliteral:
                OPEN_BRACK numlist CLOSE_BRACK {;}
        ;

numlist:
        numlist COMMA NUMBER_LITERAL {;}
        | NUMBER_LITERAL {;}
        ;

fundeclaration: FUNCTION VAR funargs RETURNING type {;}
        ;

function:	FUNCTION VAR funargs funblock {;}
        ;

funblock:	OPEN_B inblockstatements returnstatement CLOSE_B {;}
        |       OPEN_B inblockstatements CLOSE_B {;}
        ;

returnstatement:	 RETURN generaloperation SEMICOLON {;}
        |                RETURN generalexpression SEMICOLON {;}
        ;

funargs:	OPEN_P  CLOSE_P 	{;}
        | 	OPEN_P arglist CLOSE_P	{;}
        ;

arglist:	arglist COMMA arg 	{printf("arglist\n");;}
        | 	arg 			{;}
        ;

arg:	type VAR {;}
        ;

funcall:
        VAR funcallargs {printf("funcall\n");}
        ;

funcallargs:
        OPEN_P CLOSE_P {;}
        |       OPEN_P funarglist CLOSE_P {;}               
        ;

funarglist:
        funarglist COMMA funarg {printf("funarglist\n");}
        | funarg {;}
        ;

funarg:
        VAR {;}
        | STRING_LITERAL {;}
        | NUMBER_LITERAL {;}
        ;

type:		INT 	{;}
        | 	STR 	{;}
        | 	DOUBLE 	{;}
        ;

generalexpression:      generalexpression AND expression {;}
        |               generalexpression OR expression {;}
        |               expression {;}
        ;


expression: expunity EQ  expunity {;}
        |   expunity GT  expunity {;}
        |   expunity GE  expunity {;}
        |   expunity LT  expunity {;}
        |   expunity LE  expunity {;}
        |   expunity NE  expunity {;}
        |   NOT VAR               {;}
        ;

expunity:       VAR               {;}
        |       NUMBER_LITERAL    {;}
        ;

generaloperation:       operation                        {printf("%s\n",$1);}
        |               operation ADD   generaloperation {printf("%s + %s\n",$1,$3);}
        |               operation SUBS  generaloperation {printf("%s - %s\n",$1,$3);}
        ;


operation:      unity                            {/*printf("%s\n",$1)*/;}
        |       unity PROD operation             {printf("%s * %s\n",$1,$3);}
        |       unity DIV  operation             {printf("%s / %s\n",$1,$3);}
        |       unity CROSS operation            {printf("%s cross %s\n",$1,$3);}
        |       SUBS operation                   {printf("-%s\n",$1);}
        ;


unity:          VAR                             {;}
        |       NUMBER_LITERAL                  {;}
        |       arrayliteral                    {;}

%%

void yyerror(EntryPointNode ** cstring, char *s) {
	fprintf(stderr, "%s\n", s);
	printf("-------------------------------------\nError: %s in line %d\n-------------------------------------\n", s, yylineno);
	exit(0);
}

int
main(void) {

        #ifdef YYDEBUG
        yydebug = 1;
        #endif

        /*
	variables = malloc(MAX_VARIABLES * sizeof(VariableToken *));

	if (variables == NULL) {
		printf("Unable to allocate space for the variables\n");
		exit(EXIT_FAILURE);
	}
	memset(variables, '\0', sizeof(VariableToken *) * MAX_VARIABLES);
        */
	
	yyparse(&cstring);

        printf("%s\n", cstring -> testString);

        freeEntryPointNode(cstring);

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
