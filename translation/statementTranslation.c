#include "statementTranslation.h"

char * processStatement(GenericNode * gn) {
    if (gn->children == NULL){
        return NULL;
    }
    char * childString = translate(gn->children->current);
    if (childString == NULL){
        return NULL;
    }

    char * buffer = malloc(1+ strlen(";\n") + strlen(childString));
    sprintf(buffer, "%s;\n", childString);

    return buffer;
}