#include "declTranslation.h"

char * processVarDeclaration(GenericNode * gn) {
    NodeList * nl = gn->children;
    //TODO check nullity
    char * type = translate(nl->current);
    // if (type == NULL)
    //     printf("PROCESSVARDECLARATION FAIL ON TYPE");
    //     return NULL;
    nl = nl->next;
    char * var = translate(nl->current);
    // if (var == NULL)
    //     printf("PROCESSVARDECLARATION FAIL ON VAR");
    //     return NULL;
    char * numberLiteral = NULL;
    char * buffer;
    if (nl->next != NULL) {
        nl = nl->next;
        numberLiteral = translate(nl->current);
        buffer = malloc(strlen(type) + strlen(var) + strlen(numberLiteral) + 2 + 1); // 2 for brackets
        sprintf(buffer, "%s %s[%s]\n", type, var, numberLiteral);
    }
    else {
        buffer = malloc(strlen(type) + strlen(var) + 1);
        sprintf(buffer, "%s %s\n", type, var);
    }
    printf("vardeclaration %s %s %s\n", type, var, numberLiteral);
    return buffer;
}
char * processVarDeclassignment(GenericNode * gn) {
    NodeList * nl = gn->children;
    //TODO check nullity
    char * type = translate(nl->current);
    nl = nl->next;
    char * var = translate(nl->current);
    nl = nl->next;
    char * value = translate(nl->current);
    char * buffer = malloc(strlen(type) + strlen(var) + strlen(value) + 1);
    printf("Var declassignment %s %s %s\n", type, var, value);
    sprintf(buffer, "%s %s = %s", type, var, value);
    return buffer;
}