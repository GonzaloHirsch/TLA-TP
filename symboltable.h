#ifndef __SYMBOLTABLE_H__
#define __SYMBOLTABLE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VARIABLES 100
#define MAX_NAME_LENGTH 32

typedef enum {
    STRING_TYPE,
    INTEGER_TYPE,
    DOUBLE_TYPE,
    INTEGER_ARRAY_TYPE,
    DOUBLE_ARRAY_TYPE
} VarType;

typedef struct symvar{
    char name[32];
    VarType type;
    void * value;
} symvartype;

symvartype * symLook(char * name, symvartype * symvartable);

// Functions to declare variables
symvartype * symAddInt(char * name, symvartype * symvartable);
symvartype * symAddString(char * name,  symvartype * symvartable);
symvartype * symAddDouble(char * name, symvartype * symvartable);
symvartype * symAddDoubleArr(char * name, symvartype * symvartable);
symvartype * symAddIntArr(char * name, symvartype * symvartable);

// Functions to set values to variables
symvartype * symSetInt(char * name, int value, symvartype * symvartable);
symvartype * symSetString(char * name, char * value, symvartype * symvartable);
symvartype * symSetDouble(char * name, double value, symvartype * symvartable);
symvartype * symSetDoubleArr(char * name, double * values, symvartype * symvartable);
symvartype * symSetDoubleArr(char * name, double * values, symvartype * symvartable);

#endif