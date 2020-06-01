#include "opTranslation.h"

char * processPlainOp(GenericNode * gn);
char * processProdOp(GenericNode * gn);
char * processDivOp(GenericNode * gn);
char * processCrossOp(GenericNode * gn);
char * processSubOp(GenericNode * gn);
VarType determineOperationResult(VarType left, VarType right);

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

    int isLeftArray = gn->children->current->info.varType == DOUBLE_ARRAY_TYPE || gn->children->current->info.varType == INTEGER_ARRAY_TYPE;
    int isRightArray = gn->children->next->current->info.varType == DOUBLE_ARRAY_TYPE || gn->children->next->current->info.varType == INTEGER_ARRAY_TYPE;

    /*if (isLeftArray || isRightArray){
        gn->info.varType = DOUBLE_ARRAY_TYPE;
    } else if if 
    */

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

VarType determineOperationResult(VarType left, VarType right){
    if (left == right){
        return left;
    }
    // STRING TYPE COMBINATIONS
    if ((right == STRING_TYPE && left != STRING_TYPE) || (left == STRING_TYPE && right != STRING_TYPE)){
        // ERROR
    }
    // INTEGER TYPE COMBINATIONS
    if (left == INTEGER_TYPE){
        if (right == INTEGER_ARRAY_TYPE || right == DOUBLE_ARRAY_TYPE || right == DOUBLE_TYPE){
            return right;
        } else if (right == STRING_TYPE){
            // ERROR
        }
    }
    if (right == INTEGER_TYPE){
        if (left == INTEGER_ARRAY_TYPE || left == DOUBLE_ARRAY_TYPE || left == DOUBLE_TYPE){
            return right;
        } else if (left == STRING_TYPE){
            // ERROR
        }
    }
    // DOUBLE TYPE COMBINATIONS
    if (left == DOUBLE_TYPE){
        if (right == INTEGER_TYPE){
            return left;
        } else if (right == DOUBLE_ARRAY_TYPE || right == INTEGER_ARRAY_TYPE){
            return DOUBLE_ARRAY_TYPE;
        } else if (right == STRING_TYPE){
            // ERROR
        }
    }
    if (right == DOUBLE_TYPE){
        if (left == INTEGER_TYPE){
            return right;
        } else if (left == DOUBLE_ARRAY_TYPE || left == INTEGER_ARRAY_TYPE){
            return DOUBLE_ARRAY_TYPE;
        } else if (left == STRING_TYPE){
            // ERROR
        }
    }
    // INTEGER ARRAY TYPE COMBINATIONS
    if (left == INTEGER_ARRAY_TYPE){
        if (right == INTEGER_ARRAY_TYPE || right == INTEGER_TYPE){
            return left;
        } else if (right == DOUBLE_ARRAY_TYPE){
            return right;
        } else if (right == STRING_TYPE) {
            // ERROR
        }
    }
    if (right == INTEGER_ARRAY_TYPE){
        if (left == INTEGER_ARRAY_TYPE || left == INTEGER_TYPE){
            return right;
        } else if (left == DOUBLE_ARRAY_TYPE){
            return left;
        } else if (left == STRING_TYPE) {
            // ERROR
        }
    }
    // DOUBLE ARRAY TYPE COMBINATIONS
    if (left == DOUBLE_ARRAY_TYPE){
        if (right == INTEGER_ARRAY_TYPE || right == INTEGER_TYPE || right == DOUBLE_ARRAY_TYPE){
            return right;
        } else if (right == STRING_TYPE) {
            // ERROR
        }
    }
    if (right == DOUBLE_ARRAY_TYPE){
        if (left == INTEGER_ARRAY_TYPE || left == INTEGER_TYPE || left == DOUBLE_ARRAY_TYPE){
            return left;
        } else if (left == STRING_TYPE) {
            // ERROR
        }
    }
}