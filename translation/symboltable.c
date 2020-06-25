#include "symboltable.h"

/**
 *  Checks if the name of the variable is within limits and if there is not another variable with that name already
 *  Receives:
 *      -   char * name -> Pointer to the name of the variable
 *      -   ymvartype * symvartable -> Pointer to array of variables
 *  Returns:
 *      -   0 -> variable addition is not valid
 *      -   1 -> variable addition is valid
 * */
int checkVariableBeforeAdd(char * name, symvartype * symvartable);

/**
 *  Checks if the index to use is below the limit
 *  Receives:
 *      -   int varIndex -> Number of the index to use
 *  Returns:
 *      -   0 -> index is not valid
 *      -   1 -> index is valid
 * */
int checkVariableIndexStatus(int varIndex);

// ---------------------------- PRIVATE FUNCTIONS ----------------------------

int checkVariableBeforeAdd(char * name, symvartype * symvartable){
    //If name bigger than maximum name size
    if(strlen(name) > MAX_NAME_LENGTH){
        return 0;
    }

    //There is another variable with the same name
    if(symLook(name) != 0){
        return 0;
    }

    return 1;
}

int checkVariableIndexStatus(int varIndex){
    return varIndex < MAX_VARIABLES;
}

// ---------------------------- EXPOSED FUNCTIONS ----------------------------

symvartype * symLook(char * name){
    symvartype * sp;
    for(int i =0; i < MAX_VARIABLES ; i++){
        sp = &(symboltable[i]);
        // printf("THE VAR IS CALLED %s\n", sp.name);
        if(!strcmp(sp->name, name))
            return sp;
    }
    return NULL;
}

symvartype * symLookByIndex(int index){
    symvartype * sp;
    if(index < MAX_VARIABLES && index < nextFreeFunctionSlot){
        sp = &(symboltable[index]);
        if(sp->name != NULL)
            return sp;
    }
    return NULL;
}



symvartype * symAddInt(char * name){

    if (!checkVariableBeforeAdd(name, symboltable)){ return 0; }
    if (!checkVariableIndexStatus(nextFreeFunctionSlot)){ return 0; }

    symvartype * sp = &(symboltable[nextFreeFunctionSlot++]);
    strcpy(sp->name, name);
    sp->type = INTEGER_TYPE;
    sp->assigned = 0;
    sp->value = malloc(sizeof(int));
    return sp;
}

symvartype * symAddString(char * name){

    if (!checkVariableBeforeAdd(name, symboltable)){ return 0; }
    if (!checkVariableIndexStatus(nextFreeFunctionSlot)){ return 0; }

    symvartype * sp = &(symboltable[nextFreeFunctionSlot++]);
    strcpy(sp->name, name);
    sp->type = STRING_TYPE;
    sp->assigned = 0;
    return sp;
}

symvartype * symAddDouble(char * name){

    if (!checkVariableBeforeAdd(name, symboltable)){ return 0; }
    if (!checkVariableIndexStatus(nextFreeFunctionSlot)){ return 0; }

    symvartype * sp = &(symboltable[nextFreeFunctionSlot++]);
    strcpy(sp->name, name);
    sp->type = DOUBLE_TYPE;
    sp->value = malloc(sizeof(double));
    sp->assigned = 0;
    return sp;
}

symvartype * symAddDoubleArr(char * name){
    if (!checkVariableBeforeAdd(name, symboltable)){ return 0; }
    if (!checkVariableIndexStatus(nextFreeFunctionSlot)){ return 0; }

    symvartype * sp = &(symboltable[nextFreeFunctionSlot++]);
    strcpy(sp->name, name);
    sp->type = DOUBLE_ARRAY_TYPE;
    sp->value = malloc(sizeof(double *));
    sp->assigned = 0;
    return sp;
}


symvartype * symAddIntArr(char * name){
    if (!checkVariableBeforeAdd(name, symboltable)){ return 0; }
    if (!checkVariableIndexStatus(nextFreeFunctionSlot)){ return 0; }

    symvartype * sp = &(symboltable[nextFreeFunctionSlot++]);
    strcpy(sp->name, name);
    sp->type = INTEGER_ARRAY_TYPE;
    sp->value = malloc(sizeof(int *));
    sp->assigned = 0;
    return sp;
}

symvartype * symAdd(char * name, VarType type) {
    switch(type) {
        case STRING_TYPE:
            return symAddString(name);
            break;
        case INTEGER_TYPE:
            return symAddInt(name);
            break;
        case DOUBLE_TYPE:
            return symAddDouble(name);
            break;
        case INTEGER_ARRAY_TYPE:
            return symAddIntArr(name);
            break;
        case DOUBLE_ARRAY_TYPE:
            return symAddDoubleArr(name);
            break;
    }
}

void symSetAssigned(symvartype *var){
    if(var != NULL)
        var->assigned = 1;
}

int symGetAssigned(symvartype *var){
    if(var != NULL)
        return var->assigned;
    return -1;
}

symvartype * symSetInt(char * name, int value){
    symvartype * sp = symLook(name);
    if(sp->type == INTEGER_TYPE){
        *((int *) sp->value) = value;
        return sp;
    }
    
    return 0;
}

symvartype * symSetString(char * name, char * value){
    symvartype * sp = symLook(name);
    if(sp->type == STRING_TYPE){
        if(sp->value == 0){
            sp->value = malloc(strlen(value) * sizeof(char));
            strcpy((char *) sp->value, value);
        }
        else{
            sp->value = realloc(sp->value, strlen(value) * sizeof(char));
            strcpy((char *) sp->value, value);
        }
        return sp;
    }
    return 0;
}

symvartype * symSetDouble(char * name, double value){
    symvartype * sp = symLook(name);
    if(sp->type == DOUBLE_TYPE){
        *((double *) sp->value) = value;
        return sp;
    }
    
    return 0;
}

void symSet(char * name, VarType type, void * value) {
    switch(type) {
        case STRING_TYPE:
            symSetString(name, (char *) value);
            break;
        case INTEGER_TYPE:
            symSetInt(name, *((int *) value));
            break;
        case DOUBLE_TYPE:
            symSetDouble(name, *((double *) value));
            break;
        case INTEGER_ARRAY_TYPE:
            perror("not implemented: symSet for INTEGER_ARRAY_TYPE");
            break;
        case DOUBLE_ARRAY_TYPE:
            perror("not implemented: symSet for DOUBLE_ARRAY_TYPE");
            break;
    }
}
