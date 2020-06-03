#include "foreachTranslation.h"

static long lambdaCount = 0;

char * processForEach(GenericNode * gn) {

    // The VAR part
    NodeList * nl = gn->children;
    char * varName = translate(nl->current);
    //TODO check if var exists...
    
    // The METAVAR part
    nl = nl->next;
    char * metaVarName = translate(nl->current);
    //TODO checks

    // The foreachbody part
    nl = nl->next;
    // TODO error shouldn't get this far (bc yacc works OK), but maybe check
    gn = nl->current;

    char * resultingTemplate = "void _arrFunc%ld(double %s) {\n" //function declaration with global counter
                                "%s\n"    // the BLOCK/STATEMENT part (here 'body')
                                "}\n"     // Blocks inside blocks are not a problem here
                                "for(int __i = 0; __i < %s->size; __i++)\n" // this %s should be sth like arrayName->length
                                "\tarrFunc%ld(%s->arr[__i]);";    

    char * body = translate(gn);

    char * bff = malloc(strlen(varName)*2 + strlen(metaVarName)*2 + strlen(resultingTemplate) - 7);
    sprintf(bff, resultingTemplate, metaVarName, metaVarName, varName, varName);
    return bff;
}