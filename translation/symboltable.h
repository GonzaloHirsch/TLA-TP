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
    int assigned;
} symvartype;

static symvartype symboltable[MAX_VARIABLES];
static int nextFreeFunctionSlot = 0;

symvartype * symLook(char * name);
symvartype * symLookByIndex(int index);

// Functions to declare variables
symvartype * symAddInt(char * name);
symvartype * symAddString(char * name);
symvartype * symAddDouble(char * name);
symvartype * symAddDoubleArr(char * name);
symvartype * symAddIntArr(char * name);
symvartype * symAdd(char * name, VarType type);

void symSetAssigned(symvartype *var);
int symGetAssigned(symvartype *var);

// Functions to set values to variables
symvartype * symSetInt(char * name, int value);
symvartype * symSetString(char * name, char * value);
symvartype * symSetDouble(char * name, double value);
symvartype * symSetDoubleArr(char * name, double * values);
symvartype * symSetDoubleArr(char * name, double * values);
void symSet(char * name, VarType type, void * value);

#endif