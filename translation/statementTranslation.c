#include "statementTranslation.h"

char * processStatement(GenericNode * gn) {
    char * childString = process(gn->children->current);
    if (childString == NULL)
        return NULL;
    strcat(childString, ";");
    printf("a statement %s", childString);
    return childString;
}