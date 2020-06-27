#include "statementTranslation.h"

char * processStatement(GenericNode * gn) {
    if (gn->children == NULL){
        return NULL;
    }
    char * childString = translate(gn->children->current);
    if (childString == NULL){
        return NULL;
    }

    return childString;
}