#include "statementTranslation.h"

char * processStatement(GenericNode * gn) {
    char * childString = process(gn->children->current);
    strcat(childString, ";");
    printf("a statement %s", childString);
    return childString;
}