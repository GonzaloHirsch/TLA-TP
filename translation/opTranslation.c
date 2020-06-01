#include "opTranslation.h"

char * processPlainOp(GenericNode * gn);
char * processProdOp(GenericNode * gn);
char * processDivOp(GenericNode * gn);
char * processCrossOp(GenericNode * gn);
char * processSubOp(GenericNode * gn);

// ------------- EXPOSED FUNCTIONS -------------

char * processOperation(GenericNode * gn){
    char * opValue = gn->value;
    if (opValue == NULL){
        return NULL;
    }

    char * value;

    if (strcmp(opValue, "PLAIN")){
        value = processPlainOp(gn);
    } else if (strcmp(opValue, "PROD") || strcmp(opValue, "DIV") || strcmp(opValue, "CROSS")){
        value = processBinaryOp(gn);
    } else if (strcmp(opValue, "SUBS")){
        value = processSubOp(gn);
    } else {
        // UNKOWN VALUE
        printf("Compilation error: Operation non existent");
        return NULL;
    }

    return value;
}

// ------------- PRIVATE FUNCTIONS -------------

char * processPlainOp(GenericNode * gn){
    if (gn->children == NULL){
        return NULL;
    }
    return process(gn->children->current);
}

char * processProdOp(GenericNode * gn){
    if (gn->children == NULL){
        return NULL;
    }

    // Processing the left side of the operation
    char * leftSide = process(gn->children->current);
    if (leftSide == NULL){
        return NULL;
    }

    if (gn->children->next == NULL){
        return NULL;
    }

    // Processing the right side of the operation
    char * rightSide = process(gn->children->next->current);
    if (rightSide == NULL){
        return NULL;
    }

    if ()

    // Calculating and allocating buffer
    size_t bufferSize = strlen("*") + strlen(rightSide) + strlen(leftSide) + 1;
    char * buffer = malloc(bufferSize);

    // Generating the output
    sprintf(buffer, "%s + %s", leftSide, rightSide);

    return buffer;
}

char * processDivOp(GenericNode * gn){

}

char * processCrossOp(GenericNode * gn){

}

char * processSubOp(GenericNode * gn){

}