#include "foreachTranslation.h"

static long lambdaCount = 0;

char *processForEach(GenericNode *gn)
{

    // The VAR part
    NodeList *nl = gn->children;
    char *varName = translate(nl->current);

    //TODO check if var exists
    // and other integrity checks
    symvartype *svt;
    svt = symLook(varName);

    char *type;
    VarType metaVarVarType;

    switch (svt->type)
    {
    case INTEGER_ARRAY_TYPE:
        type = "int";
        metaVarVarType = INTEGER_TYPE;
        break;
    case DOUBLE_ARRAY_TYPE:
        type = "double";
        metaVarVarType = DOUBLE_TYPE;
        break;
    default:
        perror("Not a valid type for forEach. Aborting...\n");
        exit(1);
        break;
    }

    // The METAVAR part
    nl = nl->next;
    char *metaVarName = translate(nl->current);
    //TODO checks

    // The foreachbody part
    nl = nl->next;
    // TODO error shouldn't get this far (bc yacc works OK), but maybe check
    GenericNode *foreachBody = nl->current;

    changeDescendantVarType(foreachBody->children->current, metaVarName, metaVarVarType, 1); //1 for isMeta

    // Template to be used to print the function body
    char *functionTemplate = "void _arrFunc%ld(%s %s) {\n" //function declaration with global counter
                             "%s\n"                        // the BLOCK/STATEMENT part (here 'body')
                             "}\n";                        // Blocks inside blocks are not a problem here;

    // Template to be used to print the for loop
    char *forTemplate = "for(int __i = 0; __i < %s->size; __i++)\n" // this %s should be sth like arrayName->length
                        "\t_arrFunc%ld(%s->arr[__i]);\n";

    // Getting the body of the function
    char *body = translate(foreachBody->children->current);
    if (body == NULL)
    {
        return NULL;
    }

    // Counting -> length of the type + length of the metavar name + length of the function body + length of the template - 5(number of extra characters due to %...) + 20(max length of number of function)
    char *functionBuff = malloc(strlen(type) + strlen(metaVarName) + strlen(body) + strlen(functionTemplate) - 5 + 20);
    if (functionBuff == NULL)
    {
        return NULL;
    }

    // Printing the data into the template
    sprintf(functionBuff, functionTemplate, lambdaCount, type, metaVarName, body);

    // Allocating more functions
    functionDeclarations->functions = realloc(functionDeclarations->functions, (functionDeclarations->count + 1) * sizeof(struct FunctionDeclaration *));
        
    // Adding the new function
    functionDeclarations->functions[functionDeclarations->count].code = functionBuff;

    // Increasing the function count
    functionDeclarations->count++;

    // Counting -> length of variable name twice + length of template - 4(number of extra characters due to %...) + 20(max length of the variable number)
    char *forbuff = malloc(strlen(varName) * 2 + strlen(forTemplate) - 4 + 20);
    if (forbuff == NULL){
        return NULL;
    }

    // Printing the result to the template
    sprintf(forbuff, forTemplate, varName, lambdaCount, varName);
    lambdaCount++;
    return forbuff;
}