#include "opTranslation.h"

char * processPlainOp(GenericNode * gn);
char * processProdOp(GenericNode * gn);
char * processDivOp(GenericNode * gn);
char * processAddOp(GenericNode * gn);
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
        value = processDivOp(gn);
    } else if (strcmp(opValue, "ADD") == 0){
        value = processAddOp(gn);
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
    } else if (leftType == DOUBLE_TYPE && rightType == INTEGER_ARRAY_TYPE){
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
    } else if (leftType == DOUBLE_TYPE && rightType == INTEGER_ARRAY_TYPE){
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

    // Var types to determine the name of the operation
    VarType leftType = gn->children->current->info.varType;
    VarType rightType = gn->children->next->current->info.varType;
    VarType newType;
    char * operation = "*";
    char * buffer;

    // Determining the operation
    if (leftType == INTEGER_ARRAY_TYPE && rightType == INTEGER_TYPE){
        operation = "_divIntArrInt(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == INTEGER_TYPE && rightType == INTEGER_ARRAY_TYPE){
        // ERROR -> Not permited
    } else if (leftType == INTEGER_ARRAY_TYPE && rightType == DOUBLE_TYPE){
        operation = "_divIntArrDouble(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_TYPE && rightType == INTEGER_ARRAY_TYPE){
        // ERROR -> Not permited
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == DOUBLE_TYPE){
        operation = "_divDoubleArrDouble(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        // ERROR -> Not permited
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_TYPE){
        operation = "_divDoubleArrInt(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == INTEGER_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        // ERROR -> Not permited
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        operation = "_divDoubleArrDoubleArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == INTEGER_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        operation = "_divIntArrIntArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        operation = "_divDoubleArrIntArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        operation = "_divIntArrDoubleArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == INTEGER_TYPE && rightType == INTEGER_TYPE){
        operation = "(double)(/)";
        newType = INTEGER_TYPE;
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_TYPE){
        operation = "/";
        newType = DOUBLE_TYPE;
    } else if (leftType == INTEGER_TYPE && rightType == DOUBLE_TYPE){
        operation = "(double)(/)";
        newType = DOUBLE_TYPE;
    } else if (leftType == DOUBLE_TYPE && rightType == INTEGER_TYPE){
        operation = "(double)(/)";
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
        sprintf(buffer, "_divIntArrInt(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_TYPE && rightType == INTEGER_ARRAY_TYPE){
        // ERROR -> Not permited
    } else if (leftType == INTEGER_ARRAY_TYPE && rightType == DOUBLE_TYPE){
        sprintf(buffer, "_divIntArrDouble(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_TYPE && rightType == INTEGER_ARRAY_TYPE){
        // ERROR -> Not permited
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == DOUBLE_TYPE){
        sprintf(buffer, "_divDoubleArrDouble(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        // ERROR -> Not permited
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_TYPE){
        sprintf(buffer, "_divDoubleArrInt(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        // ERROR -> Not permited
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        sprintf(buffer, "_divDoubleArrDoubleArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        sprintf(buffer, "_divIntArrIntArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        sprintf(buffer, "_divDoubleArrIntArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        sprintf(buffer, "_divIntArrDoubleArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_TYPE && rightType == INTEGER_TYPE){
        sprintf(buffer, "(double)(%s/%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_TYPE){
        sprintf(buffer, "%s/%s", leftSide, rightSide);
    } else if (leftType == INTEGER_TYPE && rightType == DOUBLE_TYPE){
        sprintf(buffer, "(double)(%s/%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_TYPE && rightType == INTEGER_TYPE){
        sprintf(buffer, "(double)(%s/%s)", leftSide, rightSide);
    } else {
        // ERROR -> Operation not permitted
        printf("Operation not available, %d, %d", leftType, rightType);
    }

    return buffer;
}

char * processAddOp(GenericNode * gn){
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

    // Var types to determine the name of the operation
    VarType leftType = gn->children->current->info.varType;
    VarType rightType = gn->children->next->current->info.varType;
    VarType newType;
    char * operation = "*";
    char * buffer;

    // Determining the operation
    if (leftType == INTEGER_ARRAY_TYPE && rightType == INTEGER_TYPE){
        operation = "_sumIntArrInt(,)";
        newType = INTEGER_ARRAY_TYPE;
    } else if (leftType == INTEGER_TYPE && rightType == INTEGER_ARRAY_TYPE){
        operation = "_sumIntIntArr(,)";
        newType = INTEGER_ARRAY_TYPE;
    } else if (leftType == INTEGER_ARRAY_TYPE && rightType == DOUBLE_TYPE){
        operation = "_sumIntArrDouble(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_TYPE && rightType == INTEGER_ARRAY_TYPE){
        operation = "_sumDoubleIntArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == DOUBLE_TYPE){
        operation = "_sumDoubleArrDouble(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        operation = "_sumDoubleDoubleArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_TYPE){
        operation = "_sumDoubleArrInt(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == INTEGER_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        operation = "_sumIntDoubleArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        operation = "_sumDoubleArrDoubleArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == INTEGER_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        operation = "_sumIntArrIntArr(,)";
        newType = INTEGER_ARRAY_TYPE;
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        operation = "_sumDoubleArrIntArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        operation = "_sumIntArrDoubleArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == INTEGER_TYPE && rightType == INTEGER_TYPE){
        operation = "+";
        newType = INTEGER_TYPE;
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_TYPE){
        operation = "+";
        newType = DOUBLE_TYPE;
    } else if (leftType == INTEGER_TYPE && rightType == DOUBLE_TYPE){
        operation = "(double)(+)";
        newType = DOUBLE_TYPE;
    } else if (leftType == DOUBLE_TYPE && rightType == INTEGER_TYPE){
        operation = "(double)(+)";
        newType = DOUBLE_TYPE;
    } else if (leftType == STRING_TYPE && rightType == STRING_TYPE){
        operation = "_sumStrStr(,)";
        newType = STRING_TYPE;
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
        sprintf(buffer, "_sumIntArrInt(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_TYPE && rightType == INTEGER_ARRAY_TYPE){
        sprintf(buffer, "_sumIntArrDouble(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_ARRAY_TYPE && rightType == DOUBLE_TYPE){
        sprintf(buffer, "_sumIntArrDouble(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_TYPE && rightType == INTEGER_ARRAY_TYPE){
        sprintf(buffer, "_sumDoubleIntArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == DOUBLE_TYPE){
        sprintf(buffer, "_sumDoubleArrDouble(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        sprintf(buffer, "_sumDoubleDoubleArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_TYPE){
        sprintf(buffer, "_sumDoubleArrInt(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        sprintf(buffer, "_sumIntDoubleArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        sprintf(buffer, "_sumDoubleArrDoubleArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        sprintf(buffer, "_sumIntArrIntArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        sprintf(buffer, "_sumDoubleArrIntArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        sprintf(buffer, "_sumIntArrDoubleArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_TYPE && rightType == INTEGER_TYPE){
        sprintf(buffer, "%s+%s", leftSide, rightSide);
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_TYPE){
        sprintf(buffer, "%s+%s", leftSide, rightSide);
    } else if (leftType == INTEGER_TYPE && rightType == DOUBLE_TYPE){
        sprintf(buffer, "(double)(%s+%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_TYPE && rightType == INTEGER_TYPE){
        sprintf(buffer, "(double)(%s+%s)", leftSide, rightSide);
    } else if (leftType == STRING_TYPE && rightType == STRING_TYPE){
        sprintf(buffer, "_sumStrStr(%s,%s)", leftSide, rightSide);
    } else {
        // ERROR -> Operation not permitted
        printf("Operation not available, %d, %d", leftType, rightType);
    }

    return buffer;
}

char * processSubOp(GenericNode * gn){
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

    // Var types to determine the name of the operation
    VarType leftType = gn->children->current->info.varType;
    VarType rightType = gn->children->next->current->info.varType;
    VarType newType;
    char * operation = "*";
    char * buffer;

    // Determining the operation
    if (leftType == INTEGER_ARRAY_TYPE && rightType == INTEGER_TYPE){
        operation = "_subIntArrInt(,)";
        newType = INTEGER_ARRAY_TYPE;
    } else if (leftType == INTEGER_TYPE && rightType == INTEGER_ARRAY_TYPE){
        // ERROR -> Operation not permited
    } else if (leftType == INTEGER_ARRAY_TYPE && rightType == DOUBLE_TYPE){
        operation = "_subIntArrDouble(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_TYPE && rightType == INTEGER_ARRAY_TYPE){
        // ERROR -> Operation not permited
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == DOUBLE_TYPE){
        operation = "_subDoubleArrDouble(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        // ERROR -> Operation not permited
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_TYPE){
        operation = "_subDoubleArrInt(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == INTEGER_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        // ERROR -> Operation not permited
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        operation = "_subDoubleArrDoubleArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == INTEGER_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        operation = "_subIntArrIntArr(,)";
        newType = INTEGER_ARRAY_TYPE;
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        operation = "_subDoubleArrIntArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        operation = "_subIntArrDoubleArr(,)";
        newType = DOUBLE_ARRAY_TYPE;
    } else if (leftType == INTEGER_TYPE && rightType == INTEGER_TYPE){
        operation = "-";
        newType = INTEGER_TYPE;
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_TYPE){
        operation = "-";
        newType = DOUBLE_TYPE;
    } else if (leftType == INTEGER_TYPE && rightType == DOUBLE_TYPE){
        operation = "(double)(-)";
        newType = DOUBLE_TYPE;
    } else if (leftType == DOUBLE_TYPE && rightType == INTEGER_TYPE){
        operation = "(double)(-)";
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
        sprintf(buffer, "_subIntArrInt(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_TYPE && rightType == INTEGER_ARRAY_TYPE){
        // ERROR -> Operation not permited
    } else if (leftType == INTEGER_ARRAY_TYPE && rightType == DOUBLE_TYPE){
        sprintf(buffer, "_subIntArrDouble(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_TYPE && rightType == INTEGER_ARRAY_TYPE){
        // ERROR -> Operation not permited
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == DOUBLE_TYPE){
        sprintf(buffer, "_subDoubleArrDouble(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        // ERROR -> Operation not permited
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_TYPE){
        sprintf(buffer, "_subDoubleArrInt(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        // ERROR -> Operation not permited
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == DOUBLE_ARRAY_TYPE){
        sprintf(buffer, "_subDoubleArrDoubleArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        sprintf(buffer, "_subIntArrIntArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        sprintf(buffer, "_subDoubleArrIntArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_ARRAY_TYPE && rightType == INTEGER_ARRAY_TYPE){
        sprintf(buffer, "_subIntArrDoubleArr(%s,%s)", leftSide, rightSide);
    } else if (leftType == INTEGER_TYPE && rightType == INTEGER_TYPE){
        sprintf(buffer, "%s-%s", leftSide, rightSide);
    } else if (leftType == DOUBLE_TYPE && rightType == DOUBLE_TYPE){
        sprintf(buffer, "%s-%s", leftSide, rightSide);
    } else if (leftType == INTEGER_TYPE && rightType == DOUBLE_TYPE){
        sprintf(buffer, "(double)(%s-%s)", leftSide, rightSide);
    } else if (leftType == DOUBLE_TYPE && rightType == INTEGER_TYPE){
        sprintf(buffer, "(double)(%s-%s)", leftSide, rightSide);
    } else {
        // ERROR -> Operation not permitted
        printf("Operation not available, %d, %d", leftType, rightType);
    }

    return buffer;
}