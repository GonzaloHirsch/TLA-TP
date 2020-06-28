#include "variablesTranslation.h"

char * processVariable(GenericNode * gn) {
    char *buffer = malloc(1 + strlen(gn->value));
    sprintf(buffer, "%s", gn->value);
    return buffer;
}

char * processAssignedVariable(GenericNode * gn){
     if(gn->info.isMeta){
        char *buffer = malloc(1 + strlen(gn->value));
        sprintf(buffer, "%s", gn->value);
        return buffer;
    }

    symvartype * var = symLook(gn->value);
    if(var == NULL){
        compilationError = ERROR_UNDEFINED_VARIABLE;
        return NULL;
    }
    // If the node is variable, assign its type that just the variable knows.
    gn->info.varType = var->type;

    // Variable is now assigned
    symSetAssigned(var);

    char *buffer = malloc(1 + strlen(gn->value));
    sprintf(buffer, "%s", gn->value);
    return buffer;
}

char * processReferencedVariable(GenericNode * gn){
    if(gn->info.isMeta){
        char *buffer = malloc(1 + strlen(gn->value));
        sprintf(buffer, "%s", gn->value);
        return buffer;
    }

    symvartype * var = symLook(gn->value);
    if(var == NULL){
        compilationError = ERROR_UNDEFINED_VARIABLE;
        return NULL;
    }
    
    // If the node is variable, assign its type that just the variable knows.
    gn->info.varType = var->type;

    //Check if the variable has been ever assigned
    if(symGetAssigned(var) == 0){
        compilationError = ERROR_UNASSIGNED_VARIABLE;
        return NULL;
    }

    char *buffer = malloc(1 + strlen(gn->value));
    sprintf(buffer, "%s", gn->value);
    return buffer;
}

char * processDouble(GenericNode * gn) {
    gn->info.varType = DOUBLE_TYPE;
    char *buffer = malloc(1 + strlen(gn->value));
    sprintf(buffer, "%s", gn->value);
    return buffer;
}
char * processStr(GenericNode * gn) {
    gn->info.varType = STRING_TYPE;
    char *buffer = malloc(1 + strlen(gn->value));
    sprintf(buffer, "%s", gn->value);
    return buffer;
}

char * processInt(GenericNode * gn) {
    gn->info.varType = INTEGER_TYPE;
    char *buffer = malloc(1 + strlen(gn->value));
    sprintf(buffer, "%s", gn->value);
    return buffer;
}

char * processArrayTypeInt(GenericNode * gn){
    gn->info.varType = INTEGER_ARRAY_TYPE;
    char *buffer = malloc(1 + strlen("IntArr * "));
    sprintf(buffer, "%s", "IntArr * ");
    return buffer;
}

char * processArrayTypeDouble(GenericNode * gn){
    gn->info.varType = DOUBLE_ARRAY_TYPE;
    char *buffer = malloc(1 + strlen("DoubleArr * "));
    sprintf(buffer, "%s", "DoubleArr * ");
    return buffer;
}

char * processArray(GenericNode * gn){
    if(gn == NULL) return NULL;

    char * openB = "{";
    char * closeB = "};"; 
    char * currentValue;
    int type;

    char * buffer;

    // Gets the numlist.
    NodeList * numList = gn->children->current->children;


    //Just for the first value
    type = determineVarType(numList->current);
    currentValue = numList->current->value;
    buffer = malloc(1 + strlen(openB) + strlen(currentValue));
    sprintf(buffer, "%s%s", openB, currentValue);

    numList = numList->next;
    
    while(numList != NULL){

        // If one of the elements its double, the whole array will be double
        if(determineVarType(numList->current) == DOUBLE_TYPE){
            type = DOUBLE_TYPE;
        }

        currentValue = numList->current->value;
        buffer = realloc(buffer, 1 + strlen(buffer) + strlen(", ") + strlen(currentValue));
        strcat(buffer, ", ");
        strcat(buffer, currentValue);
        
        numList = numList->next;
    }

    buffer = realloc(buffer, 1 + strlen(buffer) + strlen(closeB));
    strcat(buffer, closeB);

    if(type == INTEGER_TYPE){
        gn->info.varType = INTEGER_ARRAY_TYPE; 
    }
    else{
        gn->info.varType = DOUBLE_ARRAY_TYPE;
    }

    return buffer;
    
}
