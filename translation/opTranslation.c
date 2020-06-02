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
        printf("Null value bitch");
        return NULL;
    }

    char * value;

    printf("MY OP VALUE %s\n", opValue);

    if (strcmp(opValue, "PLAIN") == 0){
        value = processPlainOp(gn);
    } else if (strcmp(opValue, "PROD") == 0){
        value = processProdOp(gn);
    } else if (strcmp(opValue, "DIV") == 0){

    } else if (strcmp(opValue, "CROSS") == 0){
       // value = processBinaryOp(gn);
    } else if (strcmp(opValue, "SUBS") == 0){
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
    char * value = process(gn->children->current);
    gn->info.varType = gn->children->current->info.varType;
    return value;
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

    printf("LEFT %s - RIGHT %s\n", leftSide, rightSide);

    // Var types to determine the name of the operation
    VarType leftType = gn->children->current->info.varType;
    VarType rightType = gn->children->next->current->info.varType;
    VarType newType;
    char * operation = "*";
    char * buffer;

    // Determining the operation
    if (leftType == INTEGER_ARRAY_TYPE && rightType == INTEGER_TYPE){
        operation = "_prodIntArrInt(,)";
        newType = INTEGER_ARRAY_TYPE;
    } else if (leftType == INTEGER_TYPE && rightType == INTEGER_ARRAY_TYPE){
        operation = "_prodIntIntArr(,)";
        newType = INTEGER_ARRAY_TYPE;
    } else if (leftType == INTEGER_ARRAY_TYPE && rightType == DOUBLE_TYPE){
        operation = "_prodIntArrDouble(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        operation = "_prodDoubleIntArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == DOUBLE_TYPE){
        operation = "_prodDoubleArrDouble(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        operation = "_prodDoubleDoubleArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_TYPE){
        operation = "_prodDoubleArrInt(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == INTEGER_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        operation = "_prodIntDoubleArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        operation = "_prodDoubleArrDoubleArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == INTEGER_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        operation = "_prodIntArrIntArr(,)";
        newType = INTEGER_ARRAY_TYPE;
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        operation = "_prodDoubleArrIntArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        operation = "_prodIntArrDoubleArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == INTEGER_TYPE && rightType == INTEGER_TYPE){
        operation = "*";
        newType = INTEGER_TYPE;
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_TYPE){
        operation = "*";
        newType = DOUBLE_TYPE;
    } else if (leftType == INTEGER_TYPE && rightType == DOUBLE_TYPE){
        operation = "(double)(*)";
        newType = DOUBLE_TYPE;
    } else if (leftType == DOUBLE_TYPE && rightType == INTEGER_TYPE){
        operation = "(double)(*)";
        newType = DOUBLE_TYPE;
    } else {
        // ERROR -> Operation not permitted
        printf("Operation not available, %d, %d", leftType, rightType);
    }

    // Setting the type of the new operation
    gn->info.varType = newType;

    // Calculating and allocating buffer
    size_t bufferSize = strlen(operation) + strlen(rightSide) + strlen(leftSide) + 1;
    buffer = malloc(bufferSize);

    // Generating the output
    if (leftType == INTEGER_ARRAY_TYPE && rightType == INTEGER_TYPE){
        sprintf(buffer, "_prodIntArrInt(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_TYPE && rightType == INTEGER_ARRAY_TYPE){
        sprintf(buffer, "_prodIntIntArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_ARRAY_TYPE && rightType == DOUBLE_TYPE){
        sprintf(buffer, "_prodIntArrDouble(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        sprintf(buffer, "_prodDoubleIntArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == DOUBLE_TYPE){
        sprintf(buffer, "_prodDoubleArrDouble(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        sprintf(buffer, "_prodDoubleDoubleArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_TYPE){
        sprintf(buffer, "_prodDoubleArrInt(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        sprintf(buffer, "_prodIntDoubleArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        sprintf(buffer, "_prodDoubleArrDoubleArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        sprintf(buffer, "_prodIntArrIntArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        sprintf(buffer, "_prodDoubleArrIntArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        sprintf(buffer, "_prodIntArrDoubleArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_TYPE && rightType == INTEGER_TYPE){
        sprintf(buffer, "%s*%s", leftSide, rightSide);
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_TYPE){
        sprintf(buffer, "%s*%s", leftSide, rightSide);
    } else if (leftType == INTEGER_TYPE && rightType == DOUBLE_TYPE){
        sprintf(buffer, "(double)(%s*%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_TYPE && rightType == INTEGER_TYPE){
        sprintf(buffer, "(double)(%s*%s)", leftSide, rightSide);
    } else {
        // ERROR -> Operation not permitted
        printf("Operation not available, %d, %d", leftType, rightType);
    }

    return buffer;
}

char * processDivOp(GenericNode * gn){
    return NULL;
}

char * processCrossOp(GenericNode * gn){
    return NULL;
}

char * processSubOp(GenericNode * gn){
    return NULL;
}