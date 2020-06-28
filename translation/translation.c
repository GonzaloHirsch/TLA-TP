#include "translation.h"

/**
 * Variable for the root node in order to be freed if error
*/
GenericNode *rootProgramNode;

/**
 * Function pointer to the error handler, should be yyerror()
*/
void (*handle_error)(GenericNode **, char *);

/**
 * Extern variable to hold the kind of error to be displayed
*/
CompilationErrors compilationError = ERROR_NO_ERROR;

/**
 * Extern variable to hold the declarations for the functions
*/
FunctionDeclarations functionDeclarations;

VarType determineVarType(GenericNode *gn)
{
    // Determining the type of the leaf
    VarType type;
    if (gn->value[0] == '\"')
    {
        return STRING_TYPE;
    }
    else
    {
        int i = 0;
        for (i = 0; i < strlen(gn->value); i++)
        {
            if (gn->value[i] == '.')
            {
                return DOUBLE_TYPE;
            }
        }
        return INTEGER_TYPE;
    }
}

// -------------------------- PRIVATE FUNCTIONS --------------------------

char *process(GenericNode *gn)
{
    char *value = NULL;
    if (gn == NULL)
    {
        fprintf(stderr, "Error allocating memory");
        exit(EXIT_FAILURE_);
    }
    switch (gn->info.type)
    {
    case NODE_LIST:
        break;
    case NODE_FUNCTIONS:
        break;
    case NODE_ENTRYPOINT:
        value = processEntrypointNode(gn);
        break;
    case NODE_IFSENTENCE:
        value = processIf(gn);
        break;
    case NODE_IFSENTENCE_ELSE:
        value = processIfElse(gn);
        break;
    case NODE_ELSETRAIN:
        value = processElseTrain(gn);
        break;
    case NODE_STATEMENT:
        value = processStatement(gn);
        break;
    case NODE_VARDECLARATION:
        value = processVarDeclaration(gn);
        break;
    case NODE_VARDECLASSIGNMENT:
        value = processVarDeclassignment(gn);
        break;
    case NODE_FOREACH:
        value = processForEach(gn);
        break;
    // case NODE_FOREACHBODY:
    //     value = processForEachBody(gn);
    //     break;
    case NODE_BLOCK:
        value = processBlock(gn);
        break;
    case NODE_FUNBLOCK:
        break;
    case NODE_ASSIGNMENT:
        value = processAssignment(gn);
        break;
    case NODE_INT:
        value = processInt(gn);
        break;
    case NODE_STR:
        value = processStr(gn);
        break;
    case NODE_STRING_LITERAL:
        value = processLeaf(gn);
        break;
    case NODE_DOUBLE:
        value = processDouble(gn);
        break;
    case NODE_VARIABLE:
        value = processVariable(gn);
        break;
    case NODE_VARIABLE_ASSIGNMENT:
        value = processAssignedVariable(gn);
        break;
    case NODE_VARIABLE_REF:
        value = processReferencedVariable(gn);
        break;
    case NODE_LITERAL:
        value = processLeaf(gn);
        break;
    case NODE_HYPERSTATEMENTS:
        value = processHyperStatements(gn);
        break;
    case NODE_HYPERSTATEMENT:
        value = processHyperStatement(gn);
        break;
    case NODE_INBLOCKSTATEMENTS:
        value = processInBlockStatements(gn);
        break;
    case NODE_INBLOCKSTATEMENT:
        value = processInBlockStatement(gn);
        break;
    case NODE_WHILE:
        value = processWhileNode(gn);
        break;
    case NODE_G_EXPRESSION:
        value = processGeneralExpression(gn);
        break;
    case NODE_EXPRESSION:
        value = processExpression(gn);
        break;
    case NODE_G_OPERATION:
        value = processOperation(gn);
        break;
    case NODE_OPERATION:
        value = processOperation(gn);
        break;
    case NODE_ARRAYLITERAL:
        value = processArray(gn);
        break;
    case NODE_ARR_INT:
        value = processArrayTypeInt(gn);
        break;
    case NODE_ARR_DOUBLE:
        value = processArrayTypeDouble(gn);
        break;
    case NODE_PRINT:
        value = processPrint(gn);
        break;
    case NODE_GET_INT:
        value = processGetInt(gn);
        break;
    case NODE_GET_DOUBLE:
        value = processGetDouble(gn);
        break;
    case NODE_GET_STRING:
        value = processGetString(gn);
        break;
    case NODE_ARRAY_ACCESS:
        value = processArrayAccess(gn);
        break;
    // case NODE_ARRAY_ACCESS_ASSIGNMENT:
    //     value = processArrayAccessAssignment(gn);
    //     break;
    default:
        break;
    }

    return value;
}

char *processEntrypointNode(GenericNode *gn)
{
    if (gn == NULL)
    {
        return NULL;
    }

    // Getting the nodelist with the statements
    NodeList *statementsListNode = gn->children;
    if (statementsListNode == NULL)
    {
        return NULL;
    }

    // Getting the node with the statements and processing it
    GenericNode *statementsNode = statementsListNode->current;
    char *statements = translate(statementsNode);
    if (statements == NULL)
    {
        return NULL;
    }

    // Calculating the length of the buffer
    size_t bufferSize = strlen("\nint main(){\n\nreturn 0;}\n") + strlen(statements) + 1;
    char *buffer = malloc(bufferSize);
    if (buffer == NULL)
    {
        free(statements);
        return NULL;
    }

    // Printing the strings into the buffer
    sprintf(buffer, "\nint main(){\n%s\nreturn 0;\n}", statements);

    free(statements);

    return buffer;
}

char *processHyperStatement(GenericNode *gn)
{
    // Statements add the comma,
    // won't do checks here
    return translate(gn->children->current);
}

char *processHyperStatements(GenericNode *gn)
{
    return processNodeList(gn->children);
}

char *processNodeList(NodeList *listCurrent)
{
    if (listCurrent == NULL)
        return NULL;

    char *buffer = malloc(1);
    if (buffer == NULL)
        return NULL;

    buffer[0] = '\0';

    GenericNode *currentNode;
    char *processedNode;

    //Iteration through the statement list.
    while (listCurrent != NULL)
    {
        // Getting the current Generic Node
        currentNode = listCurrent->current;
        if (currentNode == NULL)
        {
            break;
        }

        // Processing the current Generic Node
        processedNode = translate(currentNode);
        if (processedNode != NULL)
        {

            // Saving new memory for the extended buffer
            buffer = realloc(buffer, 1 + strlen(buffer) + strlen(processedNode));
            if (buffer == NULL)
            {
                //free(processedNode);
                //free(buffer);
                break;
            }

            // Concatenating the old buffer with the new processed node.
            strcat(buffer, processedNode);

             // Free the memory for the pointer to processed node
            free(processedNode);
        }

        listCurrent = listCurrent->next;
    }

    // Free the memory for the pointer to processed node
    free(processedNode);

    return buffer;
}

char *processAssignment(GenericNode *gn)
{

    if (gn == NULL)
        return NULL;

    char *buffer;
    GenericNode *varNode = gn->children->current;
    GenericNode *valueNode = gn->children->next->current;

    //Process the variable
    char *varName = translate(varNode);
    //Process the right value of the expression(literal, generalExp or genOp)
    char *valueProc = translate(valueNode);

    if (varName == NULL || valueProc == NULL)
    {
        return NULL;
    }

    if (varNode->info.varType != valueNode->info.varType)
    {
        //Check if the value assigned to the variable is valid.
        if (!(varNode->info.varType == DOUBLE_TYPE && (valueNode->info.varType == DOUBLE_TYPE || valueNode->info.varType == INTEGER_TYPE)))
        {
            compilationError = ERROR_INCOMPATIBLE_ASSIGNMENT;
            return NULL;
        }
    }

    buffer = malloc(1 + strlen(varName) + strlen(" = ;\n") + strlen(valueProc));
    if (buffer == NULL)
    {
        free(varName);
        free(valueProc);
        return NULL;
    }

    sprintf(buffer, "%s = %s;\n", varName, valueProc);

    free(varName);
    free(valueProc);

    return buffer;
}

char *processLeaf(GenericNode *gn)
{
    if (gn == NULL)
    {
        return NULL;
    }

    gn->info.varType = determineVarType(gn);

    // Creating the buffer
    size_t bufferSize = 1 + strlen(gn->value);
    char *buffer = malloc(bufferSize);
    sprintf(buffer, "%s", gn->value);

    return buffer;
}

char *processBlock(GenericNode *gn)
{
    if (gn == NULL)
        return NULL;

    char *buffer;
    char *op_b = "{\n";
    char *cl_b = "\n}";

    //Get the child node which has a inblockstament list.
    GenericNode *child = gn->children->current;
    char *processedBlock = processInBlockStatements(child);
    if (processedBlock == NULL)
    {
        return NULL;
    }

    buffer = malloc(1 + strlen(op_b) + strlen(processedBlock) + strlen(cl_b));
    if (buffer == NULL)
    {
        free(processedBlock);
        return NULL;
    }

    sprintf(buffer, "%s%s%s", op_b, processedBlock, cl_b);

    free(processedBlock);

    return buffer;
}

char *processInBlockStatements(GenericNode *gn)
{
    //Pass the children of the node, its a NodeList.
    return processNodeList(gn->children);
}

char *processInBlockStatement(GenericNode *gn)
{
    return processStatement(gn);
}

char *processWhileNode(GenericNode *gn)
{
    if (gn == NULL)
        return NULL;

    // Getting the node with the expression and processing it
    GenericNode *expressionNode = gn->children->current;
    char *expression = translate(expressionNode);
    if (expression == NULL)
    {
        return NULL;
    }

    // Getting the node with the block and processing it
    GenericNode *blockNode = gn->children->next->current;
    char *block = translate(blockNode);
    if (block == NULL)
    {
        free(expression);
        return NULL;
    }

    // Calculating the length of the buffer
    size_t bufferSize = 1 + strlen("while(  )") + strlen(block) + strlen(expression);
    char *buffer = malloc(bufferSize);
    if (buffer == NULL)
    {
        free(block);
        free(expression);
        return NULL;
    }

    // Saving the strings into the buffer
    sprintf(buffer, "while( %s )%s", expression, block);

    free(block);
    free(expression);

    return buffer;
}

char *processPrint(GenericNode *gn)
{

    if (gn == NULL)
        return NULL;

    char *buffer;

    GenericNode *childNode = gn->children->current;
    char *childNodeProc = translate(childNode);

    switch (childNode->info.varType)
    {
    case INTEGER_ARRAY_TYPE:
        buffer = malloc(1 + strlen("_printIntArr();") + strlen(childNodeProc));
        sprintf(buffer, "_printIntArr(%s);", childNodeProc);
        break;
    case DOUBLE_ARRAY_TYPE:
        buffer = malloc(1 + strlen("_printDoubleArr();") + strlen(childNodeProc));
        sprintf(buffer, "_printDoubleArr(%s);", childNodeProc);
        break;
    case STRING_TYPE:
        buffer = malloc(1 + strlen("printf(\"\"%s,\n);") + strlen(childNodeProc));
        sprintf(buffer, "printf(\"%%s\\n\",%s);", childNodeProc);
        break;
    case INTEGER_TYPE:
        buffer = malloc(1 + strlen("printf(\"\"%d,\n);") + strlen(childNodeProc));
        sprintf(buffer, "printf(\"%%d\\n\",%s);", childNodeProc);
        break;
    case DOUBLE_TYPE:
        buffer = malloc(1 + strlen("printf(\"\"%f,\n);") + strlen(childNodeProc));
        sprintf(buffer, "printf(\"%%f\\n\",%s);", childNodeProc);
        break;
    default:
        free(childNodeProc);
        return NULL;
    }

    free(childNodeProc);

    return buffer;
}

char *processGetDouble(GenericNode *gn)
{
    if (gn == NULL)
    {
        return NULL;
    }
    gn->info.varType = DOUBLE_TYPE;
    char *buffer = malloc(1 + strlen("_getDouble()"));
    if(buffer == NULL){
        return NULL;
    }
    sprintf(buffer, "_getDouble()");
    return buffer;
}

char *processGetString(GenericNode *gn)
{
    if (gn == NULL)
    {
        return NULL;
    }
    gn->info.varType = STRING_TYPE;
    char *buffer = malloc(1 + strlen("_getString()"));
    if(buffer == NULL){
        return NULL;
    }
    sprintf(buffer, "_getString()");
    return buffer;
}

char *processGetInt(GenericNode *gn)
{
    if (gn == NULL)
    {
        return NULL;
    }
    gn->info.varType = INTEGER_TYPE;
    char *buffer = malloc(1 + strlen("_getInt()"));
    if(buffer == NULL){
        return NULL;
    }
    sprintf(buffer, "_getInt()");
    return buffer;
}

char *processArrayAccess(GenericNode * gn) {
    if (gn == NULL)
        return NULL;
    
    char * buffer;
    NodeList * nl = gn->children;

    // Get the variable

    GenericNode * varNode = nl->current;
    char * var = translate(varNode);

    if (varNode->info.varType == DOUBLE_ARRAY_TYPE)
        gn->info.varType = DOUBLE_TYPE;
    if (varNode->info.varType == INTEGER_ARRAY_TYPE)
        gn->info.varType = INTEGER_TYPE;


    symvartype * svt = symLook(varNode->value);
    if (svt == NULL)
    {

        free(var);
        compilationError = ERROR_UNDEFINED_VARIABLE;
        return NULL;
    }

    // Get the expression inside brackets

    nl = nl->next;
    GenericNode * indexNode = nl->current;
    char * indexExpr = translate(indexNode);
    if(indexExpr == NULL){
        free(var);
        return NULL;
    }

    
    buffer = malloc(strlen(var) + 3 + strlen(indexExpr) + 2 + 2 + 1);
    sprintf(buffer, "%s->arr[%s]", var, indexExpr);
    free(var);
    free(indexExpr);
    return buffer;
}

// char * processArrayAccessAssignment(GenericNode * gn) {
//     ;
// }

void compose_error_message(char *buffer, int line)
{
    char *msg;
    switch (compilationError)
    {
    case ERROR_INVALID_OPERATION_TYPES:
        msg = "Invalid operation types";
        break;
    case ERROR_UNDEFINED_VARIABLE:
        msg = "Reference to undefined variable";
        break;
    case ERROR_INCOMPATIBLE_ASSIGNMENT:
        msg = "Incompatible assignment to variable";
        break;
    case ERROR_UNASSIGNED_VARIABLE:
        msg = "Reference to unassigned variable";
        break;
    case ERROR_DUPLICATED_VARIABLE:
        msg = "Duplicate variable declaration";
        break;
    case ERROR_NESTED_FOREACH:
        msg = "Nested forEach statement";
        break;
    case ERROR_GENERIC:
    default:
        msg = "Unkown error";
        break;
    }
    sprintf(buffer, "%s at line %d", msg, line);
}

// -------------------------- EXPOSED FUNCTIONS --------------------------

char *translate(GenericNode *gn)
{
    // Processing the given node
    char *code = process(gn);

    // If the given code is NULL, it means there is a compilation error
    if (code == NULL && compilationError != ERROR_NO_ERROR)
    {
        char *buffer[255] = {0};
        if (gn != NULL)
        {
            compose_error_message((char *)buffer, gn->info.line);
            handle_error(&gn, (char *)buffer);
        }
        else
        {
            compose_error_message((char *)buffer, gn->info.line);
            handle_error(&gn, (char *)buffer);
        }
    }

    return code;
}

char *translate_program(GenericNode *gn, void (*error_fun)(GenericNode **, char *))
{
    // Asigning the important error variables
    rootProgramNode = gn;
    handle_error = error_fun;

    // Allocating memory for function declarations
    functionDeclarations = malloc(sizeof(FunctionDeclarations));
    functionDeclarations->count = 0;

    // Processing the given node
    char *code = translate(gn);

    // If the given code is NULL, it means there is a compilation error
    if (code == NULL && compilationError != ERROR_NO_ERROR)
    {
        char *buffer[255] = {0};
        if (gn != NULL)
        {
            compose_error_message((char *)buffer, gn->info.line);
            handle_error(&gn, (char *)buffer);
        }
        else
        {
            compose_error_message((char *)buffer, gn->info.line);
            handle_error(&gn, (char *)buffer);
        }
    }
    return code;
}

char *getFunctionDeclarations()
{
    int i, len;
    char *result = malloc(1);
    result[0] = 0x00;

    // Iteraing all the functions declared
    for (i = 0; i < functionDeclarations->count; i++)
    {
        // Calculating length of declaration
        len = strlen(functionDeclarations->functions[i].code);
        // Allocating more memory
        result = realloc(result, strlen(result) + len + 2);
        // Printing to the result array
        sprintf(result, "%s\n%s", result, functionDeclarations->functions[i].code);
    }

    return result;
}

char *getHeaders()
{
    return "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <errno.h>\n#define BUFFERSIZE 20 \n#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))";
}

char *getInputFunctions()
{
    return "int _getInt();\nchar * _getString();\ndouble _getDouble();\nint _getInt(){\nchar c;\nchar num_buff[12] = {0};\nint index = 0;\nwhile ((c = getchar()) != EOF && c != '\\n'){\nif (c == '-' && index == 0){\nnum_buff[index++] = c;\n        } else if (c >= '0' && c <= '9'){\nif (index < 12){\nnum_buff[index++] = c;\n            } else {\nfprintf(stderr, \"\\033[0;31m\");\nprintf(\"Number out of range\\n\");\nfprintf(stderr, \"\\033[0m\");\nexit(1);\n            }\n        } else {\nfprintf(stderr, \"\\033[0;31m\");\nprintf(\"Not a number\\n\");\nfprintf(stderr, \"\\033[0m\");\nexit(1);\n        }\n    }\nint num = atoi(num_buff);\nif (num == 0 && num_buff[0] != '0'){\nfprintf(stderr, \"\\033[0;31m\");\nprintf(\"Not a number\\n\");\nfprintf(stderr, \"\\033[0m\");\nexit(1);\n    }\nreturn num;\n}\nchar * _getString(){\nchar c;\nchar * buff = malloc(1);\nint index = 0;\nwhile ((c = getchar()) != EOF && c != '\\n'){\nbuff = realloc(buff, index + 1);\nif (buff == NULL){\nfprintf(stderr, \"\\033[0;31m\");\nprintf(\"Out of memory\\n\");\nfprintf(stderr, \"\\033[0m\");\nexit(1);\n        }\nbuff[index++] = c;\n    }\nbuff = realloc(buff, index + 1);\nbuff[index] = 0x00;\nreturn buff;\n}\ndouble _getDouble(){\nchar c;\nchar num_buff[20] = {0};\nint index = 0, has_point = 0;\nwhile ((c = getchar()) != EOF && c != '\\n'){\nif (c == '.' && !has_point){\nif (index == 0){\nnum_buff[index++] = '0';\n            }\nnum_buff[index++] = c;\n        } else if (c == '-' && index == 0){\nnum_buff[index++] = c;\n        } else if (c >= '0' && c <= '9'){\nif (index < 20){\nnum_buff[index++] = c;\n            } else {\nfprintf(stderr, \"\\033[0;31m\");\nprintf(\"Number out of range\\n\");\nfprintf(stderr, \"\\033[0m\");\nexit(1);\n            }\n        } else {\nfprintf(stderr, \"\\033[0;31m\");\nprintf(\"Not a number\\n\");\nfprintf(stderr, \"\\033[0m\");\nexit(1);\n        }\n    }\nchar * stop_val;\ndouble num = strtod(num_buff, &stop_val);\nif (errno == ERANGE){\nfprintf(stderr, \"\\033[0;31m\");\nprintf(\"Number out of range\\n\");\nfprintf(stderr, \"\\033[0m\");\nexit(1);\n    } else if (num == 0 && num_buff[0] != '0'){\nfprintf(stderr, \"\\033[0;31m\");\nprintf(\"Invalid number\\n\");\nfprintf(stderr, \"\\033[0m\");\nexit(1);\n    }\nreturn num;\n}\n";
}

char *getOperationFunctions()
{
    return "\n// ------------------------- DEFINITIONS -------------------------\n\ntypedef struct IntArr{\n	int * arr;\n	int size;\n} IntArr;\n\ntypedef struct DoubleArr{\n	double * arr;\n	int size;\n} DoubleArr;\n\n// ---------- Product ----------\n\n// Product Int Arr & Int\nIntArr * _prodIntArrInt(IntArr * arr, int num);\nIntArr * _prodIntIntArr(int num, IntArr * arr);\n\n// Product Int Arr & Double\nDoubleArr * _prodIntArrDouble(IntArr * arr, double num);\nDoubleArr * _prodDoubleIntArr(double num, IntArr * arr);\n\n// Product Double Arr & Double\nDoubleArr * _prodDoubleArrDouble(DoubleArr * arr, double num);\nDoubleArr * _prodDoubleDoubleArr(double num, DoubleArr * arr);\n\n// Product Double Arr & Int\nDoubleArr * _prodDoubleArrInt(DoubleArr * arr, int num);\nDoubleArr * _prodIntDoubleArr(int num, DoubleArr * arr);\n\n// Product Double Arr & Double Arr\nDoubleArr * _prodDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2);\n\n// Product Int Arr & Int Arr\nIntArr * _prodIntArrIntArr(IntArr * arr1, IntArr * arr2);\n\n// Product Int Arr & Double Arr\nDoubleArr * _prodDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2);\nDoubleArr * _prodIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2);\n\n// ---------- Sum ----------\n\n// Sum Int Arr & Int\nIntArr * _sumIntArrInt(IntArr * arr, int num);\nIntArr * _sumIntIntArr(int num, IntArr * arr);\n\n// Sum Int Arr & Double\nDoubleArr * _sumIntArrDouble(IntArr * arr, double num);\nDoubleArr * _sumDoubleIntArr(double num, IntArr * arr);\n\n// Sum Double Arr & Double\nDoubleArr * _sumDoubleArrDouble(DoubleArr * arr, double num);\nDoubleArr * _sumDoubleDoubleArr(double num, DoubleArr * arr);\n\n// Sum Double Arr & Int\nDoubleArr * _sumDoubleArrInt(DoubleArr * arr, int num);\nDoubleArr * _sumIntDoubleArr(int num, DoubleArr * arr);\n\n// Sum Double Arr & Double Arr\nDoubleArr * _sumDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2);\n\n// Sum Int Arr & Int Arr\nIntArr * _sumIntArrIntArr(IntArr * arr1, IntArr * arr2);\n\n// Sum Int Arr & Double Arr\nDoubleArr * _sumDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2);\nDoubleArr * _sumIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2);\n\n// Sum Str & Str\nchar * _sumStrStr(char * str1, char * str2);\n\n// ---------- Subs ----------\n\n// Subs Int Arr & Int\nIntArr * _subsIntArrInt(IntArr * arr, int num);\n\n// Subs Int Arr & Double\nDoubleArr * _subsIntArrDouble(IntArr * arr, double num);\n\n// Subs Double Arr & Double\nDoubleArr * _subsDoubleArrDouble(DoubleArr * arr, double num);\n\n// Subs Double Arr & Int\nDoubleArr * _subsDoubleArrInt(DoubleArr * arr, int num);\n\n// Subs Double Arr & Double Arr\nDoubleArr * _subsDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2);\n\n// Subs Int Arr & Int Arr\nIntArr * _subsIntArrIntArr(IntArr * arr1, IntArr * arr2);\n\n// Subs Int Arr & Double Arr\nDoubleArr * _subsDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2);\nDoubleArr * _subsIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2);\n\n// ---------- Div ----------\n\n// Div Int Arr & Int\nDoubleArr * _divIntArrInt(IntArr * arr, int num);\n\n// Div Int Arr & Double\nDoubleArr * _divIntArrDouble(IntArr * arr, double num);\n\n// Div Double Arr & Double\nDoubleArr * _divDoubleArrDouble(DoubleArr * arr, double num);\n\n// Div Double Arr & Int\nDoubleArr * _divDoubleArrInt(DoubleArr * arr, int num);\n\n// Div Double Arr & Double Arr\nDoubleArr * _divDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2);\n\n// Div Int Arr & Int Arr\nDoubleArr * _divIntArrIntArr(IntArr * arr1, IntArr * arr2);\n\n// Div Int Arr & Double Arr\nDoubleArr * _divDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2);\nDoubleArr * _divIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2);\n\n//----------- Cross ----------\n\nIntArr * _crossIntArrIntArr(IntArr * arr1, IntArr * arr2);\nDoubleArr * _crossIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2);\nDoubleArr * _crossDoubleArrIntArr(DoubleArr *arr1, IntArr * arr2);\nDoubleArr * _crossDoubleArrDoubleArr(DoubleArr *arr1, DoubleArr * arr2);\n int _sprodIntArrIntArr(IntArr * arr1, IntArr * arr2);\ndouble _sprodDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2);\ndouble _sprodIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2);\ndouble _sprodDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2);\n\n// ---------- Other ----------\n\nvoid _printIntArr(IntArr * arr);\nvoid _printDoubleArr(DoubleArr * arr);\n\nint _checkArrSizes(int s1, int s2);\n\n// ------------------------- IMPLEMENTATIONS -------------------------\n\n// ---------- Product ----------\n\n// Product Int Arr & Int\nIntArr * _prodIntArrInt(IntArr * arr, int num){\n	IntArr * res = malloc(sizeof(IntArr));\n	int * resArr = malloc(sizeof(int) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (arr->arr[i] * num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\nIntArr * _prodIntIntArr(int num, IntArr * arr){\n	return _prodIntArrInt(arr, num);\n}\n\n// Product Int Arr & Double\nDoubleArr * _prodIntArrDouble(IntArr * arr, double num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] * num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\nDoubleArr * _prodDoubleIntArr(double num, IntArr * arr){\n	return _prodIntArrDouble(arr, num);\n}\n\n// Product Double Arr & Double\nDoubleArr * _prodDoubleArrDouble(DoubleArr * arr, double num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] * num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\nDoubleArr * _prodDoubleDoubleArr(double num, DoubleArr * arr){\n	return _prodDoubleArrDouble(arr, num);\n}\n\n// Product Double Arr & Int\nDoubleArr * _prodDoubleArrInt(DoubleArr * arr, int num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] * num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\nDoubleArr * _prodIntDoubleArr(int num, DoubleArr * arr){\n	return _prodDoubleArrInt(arr, num);\n}\n\n// Product Double Arr & Double Arr\nDoubleArr * _prodDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2){\n	_checkArrSizes(arr1->size, arr2->size);\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] * arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\n\n// Product Int Arr & Int Arr\nIntArr * _prodIntArrIntArr(IntArr * arr1, IntArr * arr2){\n	_checkArrSizes(arr1->size, arr2->size);\n	IntArr * res = malloc(sizeof(IntArr));\n	int * resArr = malloc(sizeof(int) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (arr1->arr[i] * arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\n\n// Product Int Arr & Double Arr\nDoubleArr * _prodDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2){\n	_checkArrSizes(arr1->size, arr2->size);\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] * arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\nDoubleArr * _prodIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2){\n	return _prodDoubleArrIntArr(arr2, arr1);\n}\n\n// ---------- Sum ----------\n\n// Sum Int Arr & Int\nIntArr * _sumIntArrInt(IntArr * arr, int num){\n	IntArr * res = malloc(sizeof(IntArr));\n	int * resArr = malloc(sizeof(int) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (arr->arr[i] + num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\nIntArr * _sumIntIntArr(int num, IntArr * arr){\n	return _sumIntArrInt(arr, num);\n}\n\n// Sum Int Arr & Double\nDoubleArr * _sumIntArrDouble(IntArr * arr, double num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] + num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\nDoubleArr * _sumDoubleIntArr(double num, IntArr * arr){\n	return _sumIntArrDouble(arr, num);\n}\n\n// Sum Double Arr & Double\nDoubleArr * _sumDoubleArrDouble(DoubleArr * arr, double num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] + num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\nDoubleArr * _sumDoubleDoubleArr(double num, DoubleArr * arr){\n	return _sumDoubleArrDouble(arr, num);\n}\n\n// Sum Double Arr & Int\nDoubleArr * _sumDoubleArrInt(DoubleArr * arr, int num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] + num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\nDoubleArr * _sumIntDoubleArr(int num, DoubleArr * arr){\n	return _sumDoubleArrInt(arr, num);\n}\n\n// Sum Double Arr & Double Arr\nDoubleArr * _sumDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2){\n	_checkArrSizes(arr1->size, arr2->size);\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] + arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\n\n// Sum Int Arr & Int Arr\nIntArr * _sumIntArrIntArr(IntArr * arr1, IntArr * arr2){\n	_checkArrSizes(arr1->size, arr2->size);\n	IntArr * res = malloc(sizeof(IntArr));\n	int * resArr = malloc(sizeof(int) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (arr1->arr[i] + arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\n\n// Sum Int Arr & Double Arr\nDoubleArr * _sumDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2){\n	_checkArrSizes(arr1->size, arr2->size);\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] + arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\nDoubleArr * _sumIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2){\n	return _sumDoubleArrIntArr(arr2, arr1);\n}\n\n// Sum Str & Str\nchar * _sumStrStr(char * str1, char * str2){\n	char * buffer = malloc(1 + strlen(str1) + strlen(str2));\n	sprintf(buffer, \"%s%s\", str1, str2);\n	return buffer;\n}\n\n// ---------- Subs ----------\n\n// Subs Int Arr & Int\nIntArr * _subsIntArrInt(IntArr * arr, int num){\n	IntArr * res = malloc(sizeof(IntArr));\n	int * resArr = malloc(sizeof(int) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (arr->arr[i] - num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\n\n// Subs Int Arr & Double\nDoubleArr * _subsIntArrDouble(IntArr * arr, double num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] - num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\n\n// Subs Double Arr & Double\nDoubleArr * _subsDoubleArrDouble(DoubleArr * arr, double num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] - num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\n\n// Subs Double Arr & Int\nDoubleArr * _subsDoubleArrInt(DoubleArr * arr, int num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] - num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\n\n// Subs Double Arr & Double Arr\nDoubleArr * _subsDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2){\n	_checkArrSizes(arr1->size, arr2->size);\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] - arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\n\n// Subs Int Arr & Int Arr\nIntArr * _subsIntArrIntArr(IntArr * arr1, IntArr * arr2){\n	_checkArrSizes(arr1->size, arr2->size);\n	IntArr * res = malloc(sizeof(IntArr));\n	int * resArr = malloc(sizeof(int) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (arr1->arr[i] - arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\n\n// Subs Int Arr & Double Arr\nDoubleArr * _subsDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2){\n	_checkArrSizes(arr1->size, arr2->size);\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] - arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\nDoubleArr * _subsIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2){\n	return _subsDoubleArrIntArr(arr2, arr1);\n}\n\n// ---------- Div ----------\n\n// Div Int Arr & Int\nDoubleArr * _divIntArrInt(IntArr * arr, int num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] / num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\n\n// Div Int Arr & Double\nDoubleArr * _divIntArrDouble(IntArr * arr, double num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] / num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\n\n// Div Double Arr & Double\nDoubleArr * _divDoubleArrDouble(DoubleArr * arr, double num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] / num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\n\n// Div Double Arr & Int\nDoubleArr * _divDoubleArrInt(DoubleArr * arr, int num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] / num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\n\n// Div Double Arr & Double Arr\nDoubleArr * _divDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2){\n	_checkArrSizes(arr1->size, arr2->size);\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] / arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\n\n// Div Int Arr & Int Arr\nDoubleArr * _divIntArrIntArr(IntArr * arr1, IntArr * arr2){\n	_checkArrSizes(arr1->size, arr2->size);\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] / arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\n\n// Div Int Arr & Double Arr\nDoubleArr * _divDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2){\n	_checkArrSizes(arr1->size, arr2->size);\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] / arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\nDoubleArr * _divIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2){\n	return _divDoubleArrIntArr(arr2, arr1);\n}\n\n//----------- Cross ----------\n\nIntArr * _crossIntArrIntArr(IntArr * arr1, IntArr * arr2){\n	_checkArrSizes(arr1->size, arr2->size);\n	if(arr1->size == 2){\n		IntArr * res = malloc(sizeof(IntArr));\n		int * resArr = malloc(sizeof(int) * 1);\n		resArr[0] = arr1->arr[0] * arr2->arr[1] - arr1->arr[1] * arr2->arr[0];\n		res->arr = resArr;\n		res->size = 1;\n		return res;\n	}\n	else if(arr1->size == 3){\n		IntArr * res = malloc(sizeof(IntArr));\n		int * resArr = malloc(sizeof(int) * 3);\n		resArr[0] = arr1->arr[1] * arr2->arr[2] - arr1->arr[2] * arr2->arr[1];\n		resArr[1] = -(arr1->arr[0] * arr2->arr[2] - arr1->arr[2] * arr2->arr[0]);\n		resArr[2] = arr1->arr[1] * arr2->arr[2] - arr1->arr[2] * arr2->arr[1];\n		res->arr = resArr;\n		res->size = 3;\n		return res;\n	}\n	else{\n		fprintf(stderr, \"Invalid size of operation between arrays\");\n		exit(0);\n	}\n}\n\nDoubleArr * _crossIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2){\n	_checkArrSizes(arr1->size, arr2->size);\n	if(arr1->size == 2){\n		DoubleArr * res = malloc(sizeof(DoubleArr));\n		double * resArr = malloc(sizeof(double) * 1);\n		resArr[0] = (double) arr1->arr[0] * arr2->arr[1] - arr1->arr[1] * arr2->arr[0];\n		res->arr = resArr;\n		res->size = 1;\n		return res;\n	}\n	else if(arr1->size == 3){\n		DoubleArr * res = malloc(sizeof(DoubleArr));\n		double * resArr = malloc(sizeof(double) * 3);\n		resArr[0] = (double) arr1->arr[1] * arr2->arr[2] - arr1->arr[2] * arr2->arr[1];\n		resArr[1] = -((double) arr1->arr[0] * arr2->arr[2] - arr1->arr[2] * arr2->arr[0]);\n		resArr[2] = (double) arr1->arr[1] * arr2->arr[2] - arr1->arr[2] * arr2->arr[1];\n		res->arr = resArr;\n		res->size = 3;\n		return res;\n	}\n	else{\n		fprintf(stderr, \"Invalid size of operation between arrays\");\n		exit(0);\n	}\n}\n\nDoubleArr * _crossDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2){\n	_checkArrSizes(arr1->size, arr2->size);\n	if(arr1->size == 2){\n		DoubleArr * res = malloc(sizeof(DoubleArr));\n		double * resArr = malloc(sizeof(double) * 1);\n		resArr[0] = (double) arr1->arr[0] * arr2->arr[1] - arr1->arr[1] * arr2->arr[0];\n		res->arr = resArr;\n		res->size = 1;\n		return res;\n	}\n	else if(arr1->size == 3){\n		DoubleArr * res = malloc(sizeof(DoubleArr));\n		double * resArr = malloc(sizeof(double) * 3);\n		resArr[0] = (double) arr1->arr[1] * arr2->arr[2] - arr1->arr[2] * arr2->arr[1];\n		resArr[1] = -((double) arr1->arr[0] * arr2->arr[2] - arr1->arr[2] * arr2->arr[0]);\n		resArr[2] = (double) arr1->arr[1] * arr2->arr[2] - arr1->arr[2] * arr2->arr[1];\n		res->arr = resArr;\n		res->size = 3;\n		return res;\n	}\n	else{\n		fprintf(stderr, \"Invalid size of operation between arrays\");\n		exit(0);\n	}\n}\n\nDoubleArr * _crossDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2){\n	_checkArrSizes(arr1->size, arr2->size);\n	if(arr1->size == 2){\n		DoubleArr * res = malloc(sizeof(DoubleArr));\n		double * resArr = malloc(sizeof(double) * 1);\n		resArr[0] = (double) arr1->arr[0] * arr2->arr[1] - arr1->arr[1] * arr2->arr[0];\n		res->arr = resArr;\n		res->size = 1;\n		return res;\n	}\n	else if(arr1->size == 3){\n		DoubleArr * res = malloc(sizeof(DoubleArr));\n		double * resArr = malloc(sizeof(double) * 3);\n		resArr[0] = (double) arr1->arr[1] * arr2->arr[2] - arr1->arr[2] * arr2->arr[1];\n		resArr[1] = -((double) arr1->arr[0] * arr2->arr[2] - arr1->arr[2] * arr2->arr[0]);\n		resArr[2] = (double) arr1->arr[1] * arr2->arr[2] - arr1->arr[2] * arr2->arr[1];\n		res->arr = resArr;\n		res->size = 3;\n		return res;\n	}\n	else{\n		fprintf(stderr, \"Invalid size of operation between arrays\");\n		exit(0);\n	}\n}\n\n\n\n// ---------- Other ----------\n\nvoid _printIntArr(IntArr * arr){\n	int i = 0;\n	printf(\"[\");\n	for (i = 0; i < arr->size; i++){\n		if (i == arr->size - 1){\n			printf(\"%d]\\n\", arr->arr[i]);\n		} else {\n			printf(\"%d \", arr->arr[i]);\n		}\n	}\n}\n\nvoid _printDoubleArr(DoubleArr * arr){\n	int i = 0;\n	printf(\"[\");\n	for (i = 0; i < arr->size; i++){\n		if (i == arr->size - 1){\n			printf(\"%f]\\n\", arr->arr[i]);\n		} else {\n			printf(\"%f \", arr->arr[i]);\n		}\n	}\n}\n\nint _checkArrSizes(int s1, int s2){\n	if(s1 != s2){\n		fprintf(stderr, \"Invalid size of operation between arrays\");\n		exit(0);\n	}\n\n	return 0;\n}\n int _sprodIntArrIntArr(IntArr * arr1, IntArr * arr2){\n _checkArrSizes(arr1 -> size, arr2 -> size);\n int res = 0, i;\n for(i = 0; i < arr1 -> size; i++){\n res += (arr1 -> arr[i] * arr2 -> arr[i] ); \n}\n return res;  \n}\n double _sprodDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2){\n_checkArrSizes(arr1->size, arr2->size);\ndouble res=0;\n int i;\n for(i = 0; i<arr1->size; i++){\n res += (arr1->arr[i] * ((double)arr2->arr[i]));  \n}\n return res; \n}\n double _sprodIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2){\n_checkArrSizes(arr1 -> size, arr2 -> size);\ndouble res=0;\n int i;\n for(i = 0; i<arr1->size; i++){\n res += (((double) arr1->arr[i]) * arr2 -> arr[i] ); \n} return res; \n}\n double _sprodDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2){\n_checkArrSizes(arr1 -> size, arr2 -> size);\ndouble res=0;\n int i;\nfor(i = 0; i <arr1->size;i++){\nres+= arr1->arr[i] * arr2->arr[i]; \n}\n return res; \n}";
}