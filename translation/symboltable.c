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
    symvartype sp;

    for(int i =0; i < MAX_VARIABLES ; i++){
        sp = symboltable[i];
        printf("THE VAR IS CALLED %s\n", sp.name);
        if(sp.name && !strcmp(sp.name, name))
            return symboltable + i * sizeof(symvartype);
    }

    return 0;
}

symvartype * symAddInt(char * name){

    if (!checkVariableBeforeAdd(name, symboltable)){ return 0; }
    if (!checkVariableIndexStatus(nextFreeFunctionSlot)){ return 0; }

    symvartype * sp = &symboltable[nextFreeFunctionSlot++];
    strcpy(sp->name, name);
    sp->type = INTEGER_TYPE;
    sp->value = malloc(sizeof(int));
    printf("JUST ADDED %s\n", symboltable[nextFreeFunctionSlot - 1].name);
    return sp;
}

symvartype * symAddString(char * name){

    if (!checkVariableBeforeAdd(name, symboltable)){ return 0; }
    if (!checkVariableIndexStatus(nextFreeFunctionSlot)){ return 0; }

    symvartype * sp = &symboltable[nextFreeFunctionSlot++];
    strcpy(sp->name, name);
    sp->type = STRING_TYPE;
    printf("JUST ADDED %s\n", symboltable[nextFreeFunctionSlot - 1].name);
    return sp;
}

symvartype * symAddDouble(char * name){

    if (!checkVariableBeforeAdd(name, symboltable)){ return 0; }
    if (!checkVariableIndexStatus(nextFreeFunctionSlot)){ return 0; }

    symvartype * sp = &symboltable[nextFreeFunctionSlot++];
    strcpy(sp->name, name);
    sp->type = DOUBLE_TYPE;
    sp->value = malloc(sizeof(double));
    printf("JUST ADDED %s\n", symboltable[nextFreeFunctionSlot - 1].name);
    return sp;
}

symvartype * symAddDoubleArr(char * name){
    if (!checkVariableBeforeAdd(name, symboltable)){ return 0; }
    if (!checkVariableIndexStatus(nextFreeFunctionSlot)){ return 0; }

    symvartype * sp = &symboltable[nextFreeFunctionSlot++];
    strcpy(sp->name, name);
    sp->type = DOUBLE_ARRAY_TYPE;
    sp->value = malloc(sizeof(double *));
    printf("JUST ADDED %s\n", symboltable[nextFreeFunctionSlot - 1].name);
    return sp;
}


symvartype * symAddIntArr(char * name){
    if (!checkVariableBeforeAdd(name, symboltable)){ return 0; }
    if (!checkVariableIndexStatus(nextFreeFunctionSlot)){ return 0; }

    symvartype * sp = &symboltable[nextFreeFunctionSlot++];
    strcpy(sp->name, name);
    sp->type = INTEGER_ARRAY_TYPE;
    sp->value = malloc(sizeof(int *));
    printf("JUST ADDED %s\n", symboltable[nextFreeFunctionSlot - 1].name);
    return sp;
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


/*
symvartype * symLook(char * name, symvartype * symvartable){
    symvartype sp;

    for(int i =0; i < MAX_VARIABLES ; i++){
        sp = symvartable[i];

        if(sp.name && !strcmp(sp.name, name))
            return symvartable + i * sizeof(symvartype);
    }

    return 0;
}

symvartype * symAddInt(char * name, symvartype * symvartable){

    if (!checkVariableBeforeAdd(name, symvartable)){ return 0; }
    if (!checkVariableIndexStatus(nextFreeFunctionSlot)){ return 0; }

    symvartype * sp = &symvartable[nextFreeFunctionSlot++];
    strcpy(sp->name, name);
    sp->type = INTEGER_TYPE;
    sp->value = malloc(sizeof(int));
    return sp;
}

symvartype * symAddString(char * name, symvartype * symvartable){

    if (!checkVariableBeforeAdd(name, symvartable)){ return 0; }
    if (!checkVariableIndexStatus(nextFreeFunctionSlot)){ return 0; }

    symvartype * sp = &symvartable[nextFreeFunctionSlot++];
    strcpy(sp->name, name);
    sp->type = STRING_TYPE;
    return sp;
}

symvartype * symAddDouble(char * name, symvartype * symvartable){

    if (!checkVariableBeforeAdd(name, symvartable)){ return 0; }
    if (!checkVariableIndexStatus(nextFreeFunctionSlot)){ return 0; }

    symvartype * sp = &symvartable[nextFreeFunctionSlot++];
    strcpy(sp->name, name);
    sp->type = DOUBLE_TYPE;
    sp->value = malloc(sizeof(double));
    return sp;
}

symvartype * symAddDoubleArr(char * name, symvartype * symvartable){
    if (!checkVariableBeforeAdd(name, symvartable)){ return 0; }
    if (!checkVariableIndexStatus(nextFreeFunctionSlot)){ return 0; }

    symvartype * sp = &symvartable[nextFreeFunctionSlot++];
    strcpy(sp->name, name);
    sp->type = DOUBLE_ARRAY_TYPE;
    sp->value = malloc(sizeof(double *));
    return sp;
}


symvartype * symAddIntArr(char * name, symvartype * symvartable){
    if (!checkVariableBeforeAdd(name, symvartable)){ return 0; }
    if (!checkVariableIndexStatus(nextFreeFunctionSlot)){ return 0; }

    symvartype * sp = &symvartable[nextFreeFunctionSlot++];
    strcpy(sp->name, name);
    sp->type = INTEGER_ARRAY_TYPE;
    sp->value = malloc(sizeof(int *));
    return sp;
}

symvartype * symSetInt(char * name, int value, symvartype * symvartable){
    symvartype * sp = symLook(name, symvartable);
    if(sp->type == INTEGER_TYPE){
        *((int *) sp->value) = value;
        return sp;
    }
    
    return 0;
}

symvartype * symSetString(char * name, char * value, symvartype * symvartable){
    symvartype * sp = symLook(name, symvartable);
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

symvartype * symSetDouble(char * name, double value, symvartype * symvartable){
    symvartype * sp = symLook(name, symvartable);
    if(sp->type == DOUBLE_TYPE){
        *((double *) sp->value) = value;
        return sp;
    }
    
    return 0;
}

*/