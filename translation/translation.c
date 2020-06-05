#include "translation.h"


VarType determineVarType(GenericNode * gn){
    // Determining the type of the leaf
    VarType type;
    if (gn->value[0] == '\"'){
        return STRING_TYPE;
    } else {
        int i = 0;
        for (i = 0; i < strlen(gn->value); i++){
            if (gn->value[i] == '.'){
                return DOUBLE_TYPE;
            }
        }
        return INTEGER_TYPE;
    }
}

// -------------------------- PRIVATE FUNCTIONS --------------------------

char * process(GenericNode * gn){
    char * value = NULL;
    if (gn == NULL){
        fprintf(stderr, "Error allocating memory");
        exit(EXIT_FAILURE_);
    }
    switch (gn->info.type){
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
        default:
            break;
    }

    return value;
}



char * processEntrypointNode(GenericNode * gn){
    if (gn == NULL){
        return NULL;
    }    

    // Getting the nodelist with the statements
    NodeList * statementsListNode = gn->children;
    if (statementsListNode == NULL){
        return NULL;
    }

    // Getting the node with the statements and processing it
    GenericNode * statementsNode = statementsListNode->current;
    char * statements = process(statementsNode);
    if (statements == NULL){
        //free(statements);
        return NULL;
    }

    // Calculating the length of the buffer
    size_t bufferSize = strlen("int main(){\n\nreturn 0;}") + strlen(statements) + 1;
    char * buffer = malloc(bufferSize);
    if (buffer == NULL){
        //free(statements);
        return NULL;
    }

    // Printing the strings into the buffer
    sprintf(buffer, "int main(){\n%s\nreturn 0;}", statements);

    //free(statements);

    return buffer;
}

char * processHyperStatement(GenericNode * gn) {
    // Statements add the comma,
    // won't do checks here
    return process(gn->children->current);
}

char * processHyperStatements(GenericNode * gn) {
    return processNodeList(gn->children);
}

char * processNodeList(NodeList * listCurrent){
    if (listCurrent == NULL) return NULL;
    
    char * buffer = malloc(1);
    if (buffer == NULL) return NULL;

    buffer[0] = '\0';  

    GenericNode * currentNode;
    char * processedNode;

    //Iteration through the statement list.
    while(listCurrent != NULL){
        // Getting the current Generic Node
        currentNode = listCurrent->current;
        if (currentNode == NULL){ 
            break; 
        }

        // Processing the current Generic Node
        processedNode = process(currentNode);
        if (processedNode == NULL){
            //free(buffer);
            break;
        }
        
        // Saving new memory for the extended buffer                             
        buffer = realloc(buffer, 1 + strlen(buffer) +  strlen(processedNode));
        if (buffer == NULL){
            //free(processedNode);
            //free(buffer);
            break;
        }

        // Concatenating the old buffer with the new processed node.
        strcat(buffer, processedNode);

        listCurrent = listCurrent->next;
    }

    // Free the memory for the pointer to processed node
    //free(processedNode);

    return buffer;
}


char * processAssignment(GenericNode * gn){

    if (gn == NULL) return NULL;

    char * buffer;
    GenericNode * varNode = gn->children->current;
    GenericNode * valueNode = gn->children->next->current;

    //Process the variable
    char * varName = process(varNode);
    //Process the right value of the expression(literal, generalExp or genOp)
    char * valueProc = process(valueNode);

   
    //Check if the value assigned to the variable is valid.
    if(varNode->info.varType != valueNode->info.varType){
        fprintf(stderr, "ERROR: Incompatible assigment of variable\n");
        exit(EXIT_FAILURE_);
    }
    

    buffer = malloc(1 + strlen(varName) + strlen(" = ") + strlen(valueProc));
    if (buffer == NULL){
        //free(valueNListProc);
        //free(varName);
        //free(buffer);
        return NULL;
    }

    sprintf(buffer, "%s = %s", varName, valueProc);

    //free(varName);
    //free(varNListProc)

    return buffer;
}

char * processLeaf(GenericNode * gn){
    if (gn == NULL){
        return NULL;
    }

    gn->info.varType = determineVarType(gn);

    // Creating the buffer
    size_t bufferSize = 1 + strlen(gn->value);
    char * buffer = malloc(bufferSize);
    sprintf(buffer, "%s", gn->value);

    return buffer;
}

char * processBlock(GenericNode * gn){
    if(gn == NULL) return NULL;
    
    char * buffer;
    char * op_b = "{\n";
    char * cl_b = "\n}";

    //Get the child node which has a inblockstament list.
    GenericNode * child = gn->children->current;
    char * processedBlock = processInBlockStatements(child);
    if(processedBlock == NULL){
        //free(buffer);
        return NULL;
    }

    buffer = malloc( 1 + strlen(op_b) + strlen(processedBlock) + strlen(cl_b));
    if(buffer == NULL){
        //free(processedBlock);
        //free(buffer);
        return NULL;
    }

    sprintf(buffer, "%s%s%s", op_b, processedBlock, cl_b);

    //free(processedBlock);

    return buffer;
}

char * processInBlockStatements(GenericNode * gn) {
    //Pass the children of the node, its a NodeList.
    return processNodeList(gn->children);
}

char * processInBlockStatement(GenericNode * gn){
    return processStatement(gn);
}

char * processWhileNode(GenericNode * gn){
    if (gn == NULL) return NULL;  

    // Getting the node with the expression and processing it
    GenericNode * expressionNode = gn->children->current;
    char * expression = process(expressionNode);
    if (expression == NULL){
        return NULL;
    }

    // Getting the node with the block and processing it 
    GenericNode * blockNode = gn->children->next->current;
    char * block = process(blockNode);
    if (block == NULL){
        return NULL;
    }

    // Calculating the length of the buffer
    size_t bufferSize = 1 + strlen("while(  )") + strlen(block) + strlen(expression);
    char * buffer = malloc(bufferSize);
    if (buffer == NULL){
        //free(block);
        //free(expression);
        return NULL;
    }

    // Saving the strings into the buffer
    sprintf(buffer, "while( %s )%s", expression, block);

    //free(block);
    //free(expression);

    return buffer;
}

char * processPrint(GenericNode * gn){

    if(gn == NULL) return NULL;

    char * buffer;
    
    GenericNode * childNode = gn->children->current;
    char * childNodeProc = process(childNode);


    switch (childNode->info.varType)
    {
    case INTEGER_ARRAY_TYPE:
        buffer = malloc(1 + strlen("_printIntArr()") + strlen(childNodeProc));
        sprintf(buffer,"_printIntArr(%s)",childNodeProc);
        break;
    case DOUBLE_ARRAY_TYPE:
        buffer = malloc(1 + strlen("_printDoubleArr()") + strlen(childNodeProc));
        sprintf(buffer,"_printDoubleArr(%s)",childNodeProc);
        break;
    case STRING_TYPE:
        buffer = malloc(1 + strlen("printf(\"\"%s,\n)") + strlen(childNodeProc));
        sprintf(buffer, "printf(\"%%s\\n\",%s)", childNodeProc);
        break;
    case INTEGER_TYPE:
        buffer = malloc(1 + strlen("printf(\"\"%d,\n)") + strlen(childNodeProc));
        sprintf(buffer, "printf(\"%%d\\n\",%s)", childNodeProc);
        break;
    case DOUBLE_TYPE:
        buffer = malloc(1 + strlen("printf(\"\"%f,\n)") + strlen(childNodeProc));
        sprintf(buffer, "printf(\"%%f\\n\",%s)", childNodeProc);
        break;
    default:
        return NULL;
        // ERROR
    }

    return buffer;
}

// -------------------------- EXPOSED FUNCTIONS --------------------------

char * translate(GenericNode * gn){
    char * code = process(gn);
    return code;
}

char * getHeadersAndFunctions(){
    return "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))\n// ------------------------- DEFINITIONS -------------------------\ntypedef struct IntArr{\n	int * arr;\n	int size;\n} IntArr;\ntypedef struct DoubleArr{\n	double * arr;\n	int size;\n} DoubleArr;\n// ---------- Product ----------\n// Product Int Arr & Int\nIntArr * _prodIntArrInt(IntArr * arr, int num);\nIntArr * _prodIntIntArr(int num, IntArr * arr);\n// Product Int Arr & Double\nDoubleArr * _prodIntArrDouble(IntArr * arr, double num);\nDoubleArr * _prodDoubleIntArr(double num, IntArr * arr);\n// Product Double Arr & Double\nDoubleArr * _prodDoubleArrDouble(DoubleArr * arr, double num);\nDoubleArr * _prodDoubleDoubleArr(double num, DoubleArr * arr);\n// Product Double Arr & Int\nDoubleArr * _prodDoubleArrInt(DoubleArr * arr, int num);\nDoubleArr * _prodIntDoubleArr(int num, DoubleArr * arr);\n// Product Double Arr & Double Arr\nDoubleArr * _prodDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2);\n// Product Int Arr & Int Arr\nIntArr * _prodIntArrIntArr(IntArr * arr1, IntArr * arr2);\n// Product Int Arr & Double Arr\nDoubleArr * _prodDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2);\nDoubleArr * _prodIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2);\n// ---------- Sum ----------\n// Sum Int Arr & Int\nIntArr * _sumIntArrInt(IntArr * arr, int num);\nIntArr * _sumIntIntArr(int num, IntArr * arr);\n// Sum Int Arr & Double\nDoubleArr * _sumIntArrDouble(IntArr * arr, double num);\nDoubleArr * _sumDoubleIntArr(double num, IntArr * arr);\n// Sum Double Arr & Double\nDoubleArr * _sumDoubleArrDouble(DoubleArr * arr, double num);\nDoubleArr * _sumDoubleDoubleArr(double num, DoubleArr * arr);\n// Sum Double Arr & Int\nDoubleArr * _sumDoubleArrInt(DoubleArr * arr, int num);\nDoubleArr * _sumIntDoubleArr(int num, DoubleArr * arr);\n// Sum Double Arr & Double Arr\nDoubleArr * _sumDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2);\n// Sum Int Arr & Int Arr\nIntArr * _sumIntArrIntArr(IntArr * arr1, IntArr * arr2);\n// Sum Int Arr & Double Arr\nDoubleArr * _sumDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2);\nDoubleArr * _sumIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2);\n// Sum Str & Str\nchar * _sumStrStr(char * str1, char * str2);\n// ---------- Subs ----------\n// Subs Int Arr & Int\nIntArr * _subsIntArrInt(IntArr * arr, int num);\n// Subs Int Arr & Double\nDoubleArr * _subsIntArrDouble(IntArr * arr, double num);\n// Subs Double Arr & Double\nDoubleArr * _subsDoubleArrDouble(DoubleArr * arr, double num);\n// Subs Double Arr & Int\nDoubleArr * _subsDoubleArrInt(DoubleArr * arr, int num);\n// Subs Double Arr & Double Arr\nDoubleArr * _subsDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2);\n// Subs Int Arr & Int Arr\nIntArr * _subsIntArrIntArr(IntArr * arr1, IntArr * arr2);\n// Subs Int Arr & Double Arr\nDoubleArr * _subsDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2);\nDoubleArr * _subsIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2);\n// ---------- Div ----------\n// Div Int Arr & Int\nDoubleArr * _divIntArrInt(IntArr * arr, int num);\n// Div Int Arr & Double\nDoubleArr * _divIntArrDouble(IntArr * arr, double num);\n// Div Double Arr & Double\nDoubleArr * _divDoubleArrDouble(DoubleArr * arr, double num);\n// Div Double Arr & Int\nDoubleArr * _divDoubleArrInt(DoubleArr * arr, int num);\n// Div Double Arr & Double Arr\nDoubleArr * _divDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2);\n// Div Int Arr & Int Arr\nDoubleArr * _divIntArrIntArr(IntArr * arr1, IntArr * arr2);\n// Div Int Arr & Double Arr\nDoubleArr * _divDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2);\nDoubleArr * _divIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2);\n// ---------- Other ----------\nvoid _printIntArr(IntArr * arr);\nvoid _printDoubleArr(DoubleArr * arr);\n// ------------------------- IMPLEMENTATIONS -------------------------\n// ---------- Product ----------\n// Product Int Arr & Int\nIntArr * _prodIntArrInt(IntArr * arr, int num){\n	IntArr * res = malloc(sizeof(IntArr));\n	int * resArr = malloc(sizeof(int) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (arr->arr[i] * num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\nIntArr * _prodIntIntArr(int num, IntArr * arr){\n	return _prodIntArrInt(arr, num);\n}\n// Product Int Arr & Double\nDoubleArr * _prodIntArrDouble(IntArr * arr, double num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] * num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\nDoubleArr * _prodDoubleIntArr(double num, IntArr * arr){\n	return _prodIntArrDouble(arr, num);\n}\n// Product Double Arr & Double\nDoubleArr * _prodDoubleArrDouble(DoubleArr * arr, double num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] * num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\nDoubleArr * _prodDoubleDoubleArr(double num, DoubleArr * arr){\n	return _prodDoubleArrDouble(arr, num);\n}\n// Product Double Arr & Int\nDoubleArr * _prodDoubleArrInt(DoubleArr * arr, int num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] * num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\nDoubleArr * _prodIntDoubleArr(int num, DoubleArr * arr){\n	return _prodDoubleArrInt(arr, num);\n}\n// Product Double Arr & Double Arr\nDoubleArr * _prodDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] * arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\n// Product Int Arr & Int Arr\nIntArr * _prodIntArrIntArr(IntArr * arr1, IntArr * arr2){\n	IntArr * res = malloc(sizeof(IntArr));\n	int * resArr = malloc(sizeof(int) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (arr1->arr[i] * arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\n// Product Int Arr & Double Arr\nDoubleArr * _prodDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] * arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\nDoubleArr * _prodIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2){\n	return _prodDoubleArrIntArr(arr2, arr1);\n}\n// ---------- Sum ----------\n// Sum Int Arr & Int\nIntArr * _sumIntArrInt(IntArr * arr, int num){\n	IntArr * res = malloc(sizeof(IntArr));\n	int * resArr = malloc(sizeof(int) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (arr->arr[i] + num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\nIntArr * _sumIntIntArr(int num, IntArr * arr){\n	return _sumIntArrInt(arr, num);\n}\n// Sum Int Arr & Double\nDoubleArr * _sumIntArrDouble(IntArr * arr, double num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] + num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\nDoubleArr * _sumDoubleIntArr(double num, IntArr * arr){\n	return _sumIntArrDouble(arr, num);\n}\n// Sum Double Arr & Double\nDoubleArr * _sumDoubleArrDouble(DoubleArr * arr, double num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] + num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\nDoubleArr * _sumDoubleDoubleArr(double num, DoubleArr * arr){\n	return _sumDoubleArrDouble(arr, num);\n}\n// Sum Double Arr & Int\nDoubleArr * _sumDoubleArrInt(DoubleArr * arr, int num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] + num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\nDoubleArr * _sumIntDoubleArr(int num, DoubleArr * arr){\n	return _sumDoubleArrInt(arr, num);\n}\n// Sum Double Arr & Double Arr\nDoubleArr * _sumDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] + arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\n// Sum Int Arr & Int Arr\nIntArr * _sumIntArrIntArr(IntArr * arr1, IntArr * arr2){\n	IntArr * res = malloc(sizeof(IntArr));\n	int * resArr = malloc(sizeof(int) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (arr1->arr[i] + arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\n// Sum Int Arr & Double Arr\nDoubleArr * _sumDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] + arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\nDoubleArr * _sumIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2){\n	return _sumDoubleArrIntArr(arr2, arr1);\n}\n// Sum Str & Str\nchar * _sumStrStr(char * str1, char * str2){\n	char * buffer = malloc(1 + strlen(str1) + strlen(str2));\n	sprintf(buffer, \"\%s\%s\", str1, str2);\n	return buffer;\n}\n// ---------- Subs ----------\n// Subs Int Arr & Int\nIntArr * _subsIntArrInt(IntArr * arr, int num){\n	IntArr * res = malloc(sizeof(IntArr));\n	int * resArr = malloc(sizeof(int) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (arr->arr[i] - num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\n// Subs Int Arr & Double\nDoubleArr * _subsIntArrDouble(IntArr * arr, double num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] - num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\n// Subs Double Arr & Double\nDoubleArr * _subsDoubleArrDouble(DoubleArr * arr, double num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] - num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\n// Subs Double Arr & Int\nDoubleArr * _subsDoubleArrInt(DoubleArr * arr, int num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] - num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\n// Subs Double Arr & Double Arr\nDoubleArr * _subsDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] - arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\n// Subs Int Arr & Int Arr\nIntArr * _subsIntArrIntArr(IntArr * arr1, IntArr * arr2){\n	IntArr * res = malloc(sizeof(IntArr));\n	int * resArr = malloc(sizeof(int) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (arr1->arr[i] - arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\n// Subs Int Arr & Double Arr\nDoubleArr * _subsDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] - arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\nDoubleArr * _subsIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2){\n	return _subsDoubleArrIntArr(arr2, arr1);\n}\n// ---------- Div ----------\n// Div Int Arr & Int\nDoubleArr * _divIntArrInt(IntArr * arr, int num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] / num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\n// Div Int Arr & Double\nDoubleArr * _divIntArrDouble(IntArr * arr, double num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] / num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\n// Div Double Arr & Double\nDoubleArr * _divDoubleArrDouble(DoubleArr * arr, double num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] / num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\n// Div Double Arr & Int\nDoubleArr * _divDoubleArrInt(DoubleArr * arr, int num){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr->size);\n	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] / num);}\n	res->arr = resArr;\n	res->size = arr->size;\n	return res;\n}\n// Div Double Arr & Double Arr\nDoubleArr * _divDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] - arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\n// Div Int Arr & Int Arr\nDoubleArr * _divIntArrIntArr(IntArr * arr1, IntArr * arr2){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] - arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\n// Div Int Arr & Double Arr\nDoubleArr * _divDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2){\n	DoubleArr * res = malloc(sizeof(DoubleArr));\n	double * resArr = malloc(sizeof(double) * arr1->size);\n	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] - arr2->arr[i]);}\n	res->arr = resArr;\n	res->size = arr1->size;\n	return res;\n}\nDoubleArr * _divIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2){\n	return _divDoubleArrIntArr(arr2, arr1);\n}\n// ---------- Other ----------\nvoid _printIntArr(IntArr * arr){\n	int i = 0;\n	printf(\"[\");\n	for (i = 0; i < arr->size; i++){\n		if (i == arr->size - 1){\n			printf(\"\%d]\\n\", arr->arr[i]);\n		} else {\n			printf(\"\%d \", arr->arr[i]);\n		}\n	}\n}\nvoid _printDoubleArr(DoubleArr * arr){\n	int i = 0;\n	printf(\"[\");\n	for (i = 0; i < arr->size; i++){\n		if (i == arr->size - 1){\n			printf(\"\%f]\\n\", arr->arr[i]);\n		} else {\n			printf(\"\%f \", arr->arr[i]);\n		}\n	}\n}";
}

