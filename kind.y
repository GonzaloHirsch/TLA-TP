%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
    #include "symboltable.h"
    #include "utility.h"
    #include "node2.h"

    void yyerror (GenericNode ** node, char *s);
    int yylex();
    
    extern int yylineno;

    GenericNode * codeRootNode;

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
}

%parse-param {struct GenericNode ** codeRootNode}

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

%type<node> entrypoint
%type<nodelist> hyperstatements
%type<node> hyperstatement
%type<node> expression
%type<node> generalexpression
%type<node> generaloperation
%type<node> operation
%type<node> unity
%type<node> expunity
%type<node> ifsentence
%type<node> statement
%type<node> block funblock
%type<nodelist> inblockstatements
%type<node> inblockstatement
%type<node> funcall fundeclaration function
%type<node> foreach foreachbody
%type<node> assignment vardeclassignment vardeclaration
%type<node> type literal
%type<node> while
%type<node> elsetrain

%%

entrypoint: 	
        START hyperstatements END 	{
        printf("entrypoint\n");
        // create node for hyprestatements
        GenericNode * hyperstatements = newGenericNode(NODE_HYPERSTATEMENTS);
        hyperstatements->children = $2;
        *codeRootNode = newGenericNodeWithChildren(NODE_ENTRYPOINT, 1, hyperstatements); $$ = *codeRootNode;
        strcpy((*codeRootNode)->testString, "helloThere\n");
        // printf("%s", c_string("int main() {", $2, "return 1;}", "", ""));
        }
        |       START END       		{
                *codeRootNode = newGenericNode(NODE_ENTRYPOINT); $$ = *codeRootNode;
                strcpy((char * )(*codeRootNode)->testString, "helloThere\n");
                }
        ;

hyperstatements: 	hyperstatement hyperstatements 	{$$ = addToNodeList($2, $1);}
        |       	hyperstatement 			{$$ = createNodeList($1);}
        ;

hyperstatement:	statement SEMICOLON 	{$$ = newGenericNodeWithChildren(NODE_HYPERSTATEMENT, 1, $1);}
        |       block   		{$$ = newGenericNodeWithChildren(NODE_HYPERSTATEMENT, 1, $1);}
        |       ifsentence        	{$$ = newGenericNodeWithChildren(NODE_HYPERSTATEMENT, 1, $1);}
        |      	while   		{$$ = newGenericNodeWithChildren(NODE_HYPERSTATEMENT, 1, $1);}
        |       function 		{$$ = newGenericNodeWithChildren(NODE_HYPERSTATEMENT, 1, $1);}
        ;

inblockstatements:	inblockstatement inblockstatements 	{$$ = addToNodeList($2, $1);}
        | 		inblockstatement 			{$$ = createNodeList($1);}
        ;
inblockstatement:	statement SEMICOLON 	{$$ = newGenericNodeWithChildren(NODE_INBLOCKSTATEMENT, 1, $1);}
        |       	ifsentence        	{$$ = newGenericNodeWithChildren(NODE_INBLOCKSTATEMENT, 1, $1);}
        |       	while   		{$$ = newGenericNodeWithChildren(NODE_INBLOCKSTATEMENT, 1, $1);}
        ;

ifsentence:	IF OPEN_P generalexpression CLOSE_P block
                {$$ = newGenericNodeWithChildren(NODE_IFSENTENCE, 2, $3, $5);}
        |       IF OPEN_P generalexpression CLOSE_P block elsetrain
                {$$ = newGenericNodeWithChildren(NODE_IFSENTENCE, 3, $3, $5, $6);}
        ;

elsetrain:	ELSE block
                {$$ = newGenericNodeWithChildren(NODE_ELSETRAIN, 1, $2);}
        |       ELSE_IF OPEN_P generalexpression CLOSE_P block
                {$$ = newGenericNodeWithChildren(NODE_ELSETRAIN, 2, $3, $5);}
        |       ELSE_IF OPEN_P generalexpression CLOSE_P block elsetrain
                {$$ = newGenericNodeWithChildren(NODE_ELSETRAIN, 3, $3, $5, $6);}
        ;

while:	WHILE OPEN_P generalexpression CLOSE_P block
        {$$ = newGenericNodeWithChildren(NODE_WHILE, 2, $3, $5);}
        ;

statement:	
                generalexpression       {$$ = newGenericNodeWithChildren(NODE_STATEMENT, 1, $1);}
        |       assignment              {$$ = newGenericNodeWithChildren(NODE_STATEMENT, 1, $1);}
        |       vardeclaration          {$$ = newGenericNodeWithChildren(NODE_STATEMENT, 1, $1);}
        |       vardeclassignment       {$$ = newGenericNodeWithChildren(NODE_STATEMENT, 1, $1);}
        |       fundeclaration          {$$ = newGenericNodeWithChildren(NODE_STATEMENT, 1, $1);}
        |       funcall                 {$$ = newGenericNodeWithChildren(NODE_STATEMENT, 1, $1);}
        |       foreach                 {$$ = newGenericNodeWithChildren(NODE_STATEMENT, 1, $1);}
        ;

vardeclaration:
                type VAR {$$ = newGenericNodeWithChildren(NODE_VARDECLARATION, 2, $1, $2);}
        |       type  VAR OPEN_BRACK NUMBER_LITERAL CLOSE_BRACK
                {$$ = newGenericNodeWithChildren(NODE_VARDECLARATION, 3, $1, $2, $4);}
        ;

vardeclassignment: 
          type VAR ASSIGN_EQ generaloperation {$$ = newGenericNodeWithChildren(NODE_VARDECLASSIGNMENT, 3, $1, $2, $4);}
        | type VAR ASSIGN_EQ literal {$$ = newGenericNodeWithChildren(NODE_VARDECLASSIGNMENT, 3, $1, $2, $4);}
        | type VAR ASSIGN_EQ generalexpression {$$ = newGenericNodeWithChildren(NODE_VARDECLASSIGNMENT, 3, $1, $2, $4);}
        ;

foreach:
        VAR DOT FOREACH OPEN_P VAR RIGHT_ARROW foreachbody CLOSE_P 
        {$$ = newGenericNodeWithChildren(NODE_FOREACH, 3, $1, $5, $7);}
        ; 
foreachbody:
        statement {$$ = newGenericNodeWithChildren(NODE_FOREACHBODY, 1, $1);}
        | funblock {$$ = newGenericNodeWithChildren(NODE_FOREACHBODY, 1, $1);}
        ;

block:	OPEN_B inblockstatements  CLOSE_B {
        // strcpy($$,c_string("{", $2, "}", "", ""));
        GenericNode * ibssNode = newGenericNode(NODE_INBLOCKSTATEMENTS);
        ibssNode->children = $2;
        $$ = newGenericNodeWithChildren(NODE_STATEMENT, 1, $1);
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

funblock:	
                OPEN_B inblockstatements returnstatement CLOSE_B {;}
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

void yyerror(GenericNode ** codeRootNode, char *s) {
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
	
	yyparse(&codeRootNode);

        printf("%s\n", codeRootNode -> testString);

        freeGenericNode(codeRootNode);

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
