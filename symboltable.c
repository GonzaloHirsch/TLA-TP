#include "symboltable.h"


symvartype * symlook(char * name, symvartype * symvartable){
    symvartype sp;

    for(int i =0; i < MAX_VARIABLES ; i++){
        sp = symvartable[i];

        if(sp.name && !strcmp(sp.name, name))
            return symvartable + i * sizeof(symvartype);
    }

    return 0;
}

symvartype * symaddInt(char * name, symvartype * symvartable){

    symvartype * sp;

    //If name bigger than maximum name size
    if(strlen(name) > MAX_NAME_LENGTH){
        return 0;
    }

    //There is another variable with the same name
    if(symlook(name, symvartable) != 0){
        return 0;
    }

    for(sp = symvartable; sp < &symvartable[MAX_VARIABLES]; sp++){

        if(!sp->name){
            strcpy(sp->name, name);
            sp->type = INTEGER_TYPE;
            sp->value = malloc(sizeof(int));
            return sp; 
        }
    }

    //All variables are full.
    return 0;
}

symvartype * symaddString(char * name, symvartype * symvartable){

    symvartype * sp;

    if(strlen(name) > MAX_NAME_LENGTH){
        return 0;
    }
    if(symlook(name, symvartable) != 0){
        return 0;
    }

    for(sp = symvartable; sp < &symvartable[MAX_VARIABLES]; sp++){

        if(!sp->name){
            strcpy(sp->name, name);
            sp->type = STRING_TYPE;
            return sp; 
        }
    }

    //All variables are full.
    return 0;
}

symvartype * symaddDouble(char * name, symvartype * symvartable){

    symvartype * sp;

    if(strlen(name) > MAX_NAME_LENGTH){
        return 0;
    }

    if(symlook(name, symvartable) != 0){
        return 0;
    }

    for(sp = symvartable; sp < &symvartable[MAX_VARIABLES]; sp++){

        if(!sp->name){
            strcpy(sp->name, name);
            sp->type = DOUBLE_TYPE;
            sp->value = malloc(sizeof(double));

            return sp; 
        }
    }

    return 0;
}

symvartype * symSetInt(char * name, int value, symvartype * symvartable){
    symvartype * sp = simlook(name,symvartable);
    if(sp->type == INTEGER_TYPE){
        *((int *) sp->value) = value;
        return sp;
    }
    
    return 0;
}

symvartype * symSetString(char * name, char * value, symvartype * symvartable){
    symvartype * sp = simlook(name,symvartable);
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
    symvartype * sp = simlook(name,symvartable);
    if(sp->type == DOUBLE_TYPE){
        *((double *) sp->value) = value;
        return sp;
    }
    
    return 0;
}

