#include "expressionTranslation.h"

char * processGeneralExpression(GenericNode * gn){
    char * buffer = malloc(1);
    if (buffer == NULL) {
        return NULL;
    }
    buffer[0] = '\0';
    char * operatorValue = gn -> value;
    char * op;

    if(strcmp(operatorValue, "AND") == 0){
        op = " && ";
    }
    else if(strcmp(operatorValue, "OR") == 0)
    {   
        op = " || ";
    }
    else{
        op = "";
    }

    GenericNode * exp1 = gn -> children ->current;
    char * exp1Proc = translate(exp1);


    if(strcmp(op, "") != 0){ //there is an operator to parse, then there is another expression
        GenericNode * exp2 = gn -> children -> next ->current;
        char * exp2Proc = translate(exp2);
        if(exp2Proc == NULL){
            //free(buffer);
            return NULL;
        }
        buffer = realloc(buffer, 1 + strlen(exp1Proc) + strlen(op) + strlen(exp2Proc) + strlen(buffer));
        if(buffer == NULL){
            //free(exp1Proc);
            //free(exp2Proc);
            return NULL;
        }
        strcat(buffer, exp1Proc);
        strcat(buffer, op);
        strcat(buffer, exp2Proc);

        //free(exp1Proc);
        //free(exp2Proc);

        return buffer;

    }

    // there is no other expression

    buffer = realloc(buffer,1+ strlen(exp1Proc) + strlen(buffer));
    if(buffer == NULL){
        //free(exp1Proc);
        return NULL;
    }
    strcat(buffer, exp1Proc);

    // A general expression is of integer type.
    gn->info.varType = INTEGER_TYPE;

    //free(exp1Proc);

    return buffer;
}


char * processExpression(GenericNode * gn){
    char * buffer = malloc(1);
    if (buffer == NULL) {
        return NULL;
    }
    buffer[0] = '\0';

    GenericNode * exp1 = gn ->children -> current;
    char * exp1Proc = translate(exp1);
    if(exp1Proc == NULL){
        free(buffer);
        return NULL;
    }

    char * opString = gn -> value;
    char * op;
    if(strcmp(opString, "EQ") == 0){
        op = " == ";
    }
    else if(strcmp(opString, "GT") == 0){
        op = " > ";
    }
    else if(strcmp(opString, "GE") == 0){
        op = " >= ";
    }
    else if(strcmp(opString, "LT") == 0){
        op = " < ";
    }
    else if(strcmp(opString, "LE") == 0){
        op = " <= ";
    }
    else if(strcmp(opString, "NE") == 0){
        op = " != ";
    }
    else if(strcmp(opString, "NOT") == 0){
        op = " !";

        // check that if exp1 its a variable, its a valid type.
        if(exp1->info.varType != INTEGER_TYPE && exp1->info.varType != DOUBLE_TYPE){
            compilationError = ERROR_INVALID_COMPARISON;
            return NULL;
        }

        buffer = realloc(buffer,1 + strlen(op) + strlen(exp1Proc) + strlen(buffer));
        if(buffer == NULL){
            free(exp1Proc);
            return NULL;
        }

        strcat(buffer, op);
        strcat(buffer, exp1Proc);

        free(exp1Proc);

        return buffer;

    }
    
    // is not an unary expression

    GenericNode * exp2 = gn -> children -> next -> current;
    char * exp2Proc = translate(exp2);
    if(exp2Proc == NULL){
        free(buffer);
        free(exp1Proc);
        return NULL;
    }

     // check that if exp1 or exp2 are a variable, its a valid type.
        if((exp1->info.varType != INTEGER_TYPE && exp1->info.varType != DOUBLE_TYPE) || (exp2->info.varType != INTEGER_TYPE && exp2->info.varType != DOUBLE_TYPE)){
            perror("Invalid type in expression\n");
            exit(EXIT_FAILURE_);
        }



    buffer = realloc(buffer,1+ strlen(op) + strlen(exp1Proc) + strlen(exp2Proc) + strlen(buffer));
    if(buffer == NULL){
        free(exp1Proc);
        free(exp2Proc);
        return NULL;
    }

    //example:  var1 >= var2
    strcat(buffer, exp1Proc);
    strcat(buffer, op);
    strcat(buffer, exp2Proc);
    free(exp1Proc);
    free(exp2Proc);


    return buffer;

}