#ifndef __SYMBOLTABLE_H__
#define __SYMBOLTABLE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VARIABLES 100

typedef enum {
    STRING,
    INTEGER,
    DOUBLE
} VarType;

typedef struct symvar{
    char name[32];
    VarType type;
    void * value;
} symvartype;

symvartype * symlook(char * name, symvartype * symvartable);
struct symvar * symaddInt(char * name, int value, symvartype * symvartable);
struct symvar * symaddString(char * name, char * value, symvartype * symvartable);
struct symvar * symaddDouble(char * name, double value, symvartype * symvartable);

#endif