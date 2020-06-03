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

    char * buffer;
    NodeList * nl = gn->children;

    // Get the type
    GenericNode * typeNode = nl->current;
    char * type = translate(typeNode);
    if(type == NULL){
        return NULL;
    }

    //Get the variable
    nl = nl->next;
    GenericNode * varNode = nl->current;
    char * var = translate(varNode);
    if(var == NULL){
        //free(type);
        return NULL;
    }

    //Get the right value.
    nl = nl->next;
    GenericNode * valueNode = nl->current;
    char * value = translate(valueNode);
    if(value == NULL){
        //free(type);
        //free(var);
        return NULL;
    }

    if(typeNode->info.varType == INTEGER_ARRAY_TYPE){
        char * intArrDec = "int _%s[] = %s;\nIntArr * %s = malloc(sizeof(IntArr));\n%s->arr = _%s;\n%s->size = NELEMS(_%s);\n";
        buffer = malloc(1 + strlen(intArrDec) + 6*strlen(var) +strlen(value) );
        sprintf(buffer, intArrDec, var, value, var, var, var, var,var);

    }
    else if(typeNode->info.varType == DOUBLE_ARRAY_TYPE){
        char * doubleArrDec = "double _%s[] = %s;\nDoubleArr * %s = malloc(sizeof(DoubleArr));\n%s->arr = _%s;\n%s->size = NELEMS(_%s);\n";
        buffer = malloc(1 + strlen(doubleArrDec) + 6*strlen(var) +strlen(value) );
        sprintf(buffer, doubleArrDec, var, value, var, var, var, var,var);
    }
    else{
        buffer = malloc(strlen(type) + strlen(var) + strlen(value) + strlen(" =  ") + 1);
        sprintf(buffer, "%s %s = %s", type, var, value);
    }
    
    return buffer;
}