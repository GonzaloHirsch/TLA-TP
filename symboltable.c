#include "symboltable.h"


struct symvar * symlook(char * name, symvartype * symvartable){
    symvartype sp;

    for(int i =0; i < MAX_VARIABLES ; i++){
        sp = symvartable[i];

        if(sp.name && !strcmp(sp.name, name))
            return symvartable + i * sizeof(symvartype);
    }

    return 0;
}

struct symvar * symaddInt(char * name, int value, symvartype * symvartable){

    symvartype * sp;

    //
    if(strlen(name) > 32){
        return 0;
    }

    //There is another variable with the same name
    if(symlook(name, symvartable) != 0){
        return 0;
    }

    for(sp = symvartable; sp < &symvartable[MAX_VARIABLES]; sp++){

        if(!sp->name){
            strcpy(sp->name, name);
            sp->type = INTEGER;
            sp->value = malloc(sizeof(int));
            *((int *) sp->value) = value;
            return sp; 
        }
    }

    //All variables are full.
    return 0;
}

struct symvar * symaddString(char * name, char * value, symvartype * symvartable){

    symvartype * sp;

    //
    if(strlen(name) > 32){
        return 0;
    }

    //There is another variable with the same name
    if(symlook(name, symvartable) != 0){
        return 0;
    }

    for(sp = symvartable; sp < &symvartable[MAX_VARIABLES]; sp++){

        if(!sp->name){
            strcpy(sp->name, name);
            sp->type = STRING;
            sp->value = malloc(strlen(value) * sizeof(char));
            strcpy((char *) sp->value, value);
            return sp; 
        }
    }

    //All variables are full.
    return 0;
}

struct symvar * symaddDouble(char * name, double value, symvartype * symvartable){

    symvartype * sp;

    //
    if(strlen(name) > 32){
        return 0;
    }

    //There is another variable with the same name
    if(symlook(name, symvartable) != 0){
        return 0;
    }

    for(sp = symvartable; sp < &symvartable[MAX_VARIABLES]; sp++){

        if(!sp->name){
            strcpy(sp->name, name);
            sp->type = DOUBLE;
            sp->value = malloc(sizeof(double));
            *((double *) sp->value) = value;
            return sp; 
        }
    }

    //All variables are full.
    return 0;
}

