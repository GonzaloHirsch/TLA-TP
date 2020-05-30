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

%type<string> hyperstatements
%type<string> hyperstatement
%type<string> entrypoint
%type<string> expression
%type<string> generalexpression
%type<string> generaloperation
%type<string> operation
%type<string> ifsentence
%type<string> statement
%type<string> block
%type<string> inblockstatements
%type<string> inblockstatement
%type<string> funcall

%%

entrypoint: 	START hyperstatements END 	{
        printf("entrypoint\n");
        // printf("%s", c_string("int main() {", $2, "return 1;}", "", ""));
        }
        |       START END       		{
                printf("int main(){ return 1; }") ;
                }
        ;

hyperstatements: 	hyperstatement hyperstatements 	{;}
        |       	hyperstatement 			{
                // strcpy($$, $1);
                        ;
                }
        ;

hyperstatement:	statement SEMICOLON 	{
        // strcpy($$, strcat($1,";"));
                ;
        }
        |       block   		{;}
        |       ifsentence        	{;}
        |      	while   		{;}
        |       function 		{;}
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
        |       arrayliteral {;}
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
        |   NOT VAR                {;}
        ;

generaloperation: generaloperation ADD  generaloperation  {printf("general operation ADD\n");}
        |         generaloperation SUBS generaloperation  {printf("general operation SUBS\n");;}
        |         generaloperation DIV  generaloperation  {printf("general operation DIV\n");;}
        |         generaloperation PROD generaloperation  {printf("general operation PROD\n");;}     
        |         operation                               {printf("general operation raw\n");;}
        ;


operation:      VAR ADD VAR                     {;}
        |       VAR SUBS VAR                    {;}
        |       VAR DIV VAR                     {;}
        |       VAR PROD VAR                    {;}
        |       VAR ADD NUMBER_LITERAL          {;}
        |       VAR SUBS NUMBER_LITERAL         {;}
        |       VAR DIV NUMBER_LITERAL          {;}
        |       VAR PROD NUMBER_LITERAL         {;}
        |       VAR CROSS VAR                   {
                printf("%s %s cross %s // var cross var\n", $$, $1, $3);
                }
        |       NUMBER_LITERAL ADD VAR          {;}
        |       NUMBER_LITERAL SUBS VAR         {;}
        |       NUMBER_LITERAL DIV VAR          {;}
        |       NUMBER_LITERAL PROD VAR         {;}
        |       NUMBER_LITERAL ADD NUMBER_LITERAL          {;}
        |       NUMBER_LITERAL SUBS NUMBER_LITERAL         {;}
        |       NUMBER_LITERAL DIV NUMBER_LITERAL          {;}
        |       NUMBER_LITERAL PROD NUMBER_LITERAL         {;}

        |       NUMBER_LITERAL ADD arrayliteral           {printf("numb literal add array literal\n");}
        |       arrayliteral  ADD arrayliteral           {printf("array literal add array literal\n");}
        |       arrayliteral  ADD NUMBER_LITERAL          {printf("array literal add num literal\n");}
        |       arrayliteral  SUBS arrayliteral          {printf("array literal subs array literal\n");}
        |       arrayliteral  SUBS NUMBER_LITERAL         {printf("array literal subs num literal\n");}
        |       NUMBER_LITERAL  PROD arrayliteral          {printf("num literal prod array literal\n");}
        |       arrayliteral  PROD arrayliteral           {printf("array literal prod array literal\n");}
        |       arrayliteral  PROD NUMBER_LITERAL         {printf("array literal prod num literal\n");}
        |       arrayliteral  DIV NUMBER_LITERAL         {printf("array literal div num literal\n");}
        |       arrayliteral CROSS      arrayliteral    {printf("arraylit cross arraylit\n");}

        |       arrayliteral ADD VAR    {;}
        |       arrayliteral SUBS VAR    {;}
        |       arrayliteral PROD VAR    {;}
        |       arrayliteral DIV VAR    {;}
        |       arrayliteral CROSS VAR  {;}
        |       VAR ADD arrayliteral    {;}
        |       VAR SUBS arrayliteral    {;}
        |       VAR PROD arrayliteral    {;}
        |       VAR CROSS arrayliteral    {;}

        |       SUBS VAR                                   {;}
        |       VAR                                        {;}
        |       NUMBER_LITERAL                             {;}
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
