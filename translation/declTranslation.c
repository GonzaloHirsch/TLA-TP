#include "declTranslation.h"

char * processVarDeclaration(GenericNode * gn) {
    NodeList * nl = gn->children;
    //TODO check nullity
    char * type = translate(nl->current);
    nl = nl->next;
    char * var = translate(nl->current);
    char * numberLiteral = NULL;
    if (nl->next != NULL) {
        nl = nl->next;
        numberLiteral = translate(nl->current);
    }
    char * buffer = malloc(strlen(type) + strlen(var) + (numberLiteral == NULL) ? 0 : strlen(numberLiteral));
    sprintf(buffer, "%s %s = %s\n", type, var, numberLiteral);
    return buffer;
}
char * processVarDeclassignment(GenericNode * gn) {
    
    return "processVarDeclassignment";
}