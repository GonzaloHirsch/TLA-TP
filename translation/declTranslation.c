#include "declTranslation.h"

char * processVarDeclaration(GenericNode * gn) {
    if(gn == NULL) return NULL;

    NodeList * nl = gn->children;
    char * type = translate(nl->current);
    if (type == NULL){
        printf("PROCESSVARDECLARATION FAIL ON TYPE");
        return NULL;
    }   

    nl = nl->next;
    char * var = translate(nl->current);
    if (var == NULL){
        printf("PROCESSVARDECLARATION FAIL ON VAR");
        //free(type)
        return NULL;
    }

    char * numberLiteral = NULL;
    char * buffer;

    if (nl->next != NULL) {
        nl = nl->next;
        numberLiteral = translate(nl->current);
        buffer = malloc(strlen(type) + strlen(var) + strlen(numberLiteral) + 4 + 1); // 2 for brackets, 1 for space,1 for \n,  1 for \0
        sprintf(buffer, "%s %s[%s]\n", type, var, numberLiteral);
    }
    else {
        buffer = malloc(strlen(type) + strlen(var) + 1 + 1);
        sprintf(buffer, "%s %s\n", type, var);
    }

    printf("vardeclaration %s %s %s\n", type, var, numberLiteral);

    return buffer;
}


char * processVarDeclassignment(GenericNode * gn) {
    if(gn == NULL) return NULL;

    NodeList * nl = gn->children;

    // Get the type
    char * type = translate(nl->current);
    if(type == NULL){
        return NULL;
    }

    //Get the variable
    nl = nl->next;
    char * var = translate(nl->current);
    if(var == NULL){
        //free(type);
        return NULL;
    }

    //Get the right value.
    nl = nl->next;
    char * value = translate(nl->current);
    if(value == NULL){
        //free(type);
        //free(var);
        return NULL;
    }

    char * buffer = malloc(strlen(type) + strlen(var) + strlen(value) + strlen(" =  ") + 1);
    sprintf(buffer, "%s %s = %s", type, var, value);

    printf("Var declassignment %s\n", buffer);
    return buffer;
}