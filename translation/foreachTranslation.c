#include "foreachTranslation.h"

static long lambdaCount = 0;

char * processForEach(GenericNode * gn) {

    // The VAR part
    NodeList * nl = gn->children;
    char * varName = translate(nl->current);
    
    //TODO check if var exists
    // and other integrity checks
    symvartype * svt;
    svt = symLook(varName);
    
    char * type;
    VarType metaVarVarType;

    switch(svt->type) {
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
    char * metaVarName = translate(nl->current);
    //TODO checks

    // The foreachbody part
    nl = nl->next;
    // TODO error shouldn't get this far (bc yacc works OK), but maybe check
    GenericNode * foreachBody = nl->current;

    changeDescendantVarType(foreachBody->children->current, metaVarName, metaVarVarType, 1); //1 for isMeta

    char * resultingTemplate = "void _arrFunc%ld(%s %s) {\n" //function declaration with global counter
                                "%s\n"    // the BLOCK/STATEMENT part (here 'body')
                                "}\n"     // Blocks inside blocks are not a problem here
                                "for(int __i = 0; __i < %s->size; __i++)\n" // this %s should be sth like arrayName->length
                                "\t_arrFunc%ld(%s->arr[__i])";    

    char * body = translate(foreachBody->children->current);

    char * bff = malloc(strlen(type) + strlen(varName)*2 + strlen(metaVarName) + strlen(body) + strlen(resultingTemplate) - 9 + 16); //16 for the dubious length of the global variable 
    sprintf(bff, resultingTemplate, lambdaCount, type, metaVarName, body, varName, lambdaCount, varName);
    lambdaCount++;
    return bff;
}