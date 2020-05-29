#include "utility.h"





char * c_string(int argCount, ...){
    int size;
    char **arguments = (char **)malloc(argCount * sizeof(char *));
    
    va_list ap;

    va_start(ap, argCount);

    int i;
    for(i = 0; i < argCount; i++){
        arguments[i] = va_arg(ap, char *);
        size += strlen(arguments[i]);
    }

    char * concatenation = (char *) malloc((size + 1) * sizeof(char));

    strcpy(concatenation, arguments[0]); //need to copy first argument

    for(i = 1; i < argCount; i++){
        strcat(concatenation, arguments[i]);
        free(arguments[i]); //free resources mallocated before
    }



    return concatenation;

}


