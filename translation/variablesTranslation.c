#include "variablesTranslation.h"

char * processVariable(GenericNode * gn) {
    printf("variable with value %s\n", gn->value);
    printf("BEFORE THE VAR\n");
    symvartype * var = symLook(gn->value);
    if (var == NULL){
        var = symAdd(gn->value, gn->info.varType);
    }
    printf("AFTER THE VAR\n");
    gn->info.varType = var->type;
    return gn->value;
}
char * processDouble(GenericNode * gn) {
    printf("double with value %s\n", gn->value);
    gn->info.varType = DOUBLE_TYPE;
    return gn->value;
}
char * processStr(GenericNode * gn) {
    printf("str with value %s\n", gn->value);
    gn->info.varType = STRING_TYPE;
    return gn->value;
}

char * processInt(GenericNode * gn) {
    printf("Int with value %s\n", gn->value);
    gn->info.varType = INTEGER_TYPE;
    return gn->value;
}

char * processArrayTypeInt(GenericNode * gn){
    gn->info.varType = INTEGER_ARRAY_TYPE;
    return "IntArr * ";
}

char * processArrayTypeDouble(GenericNode * gn){
    gn->info.varType = DOUBLE_ARRAY_TYPE;
    return "DoubleArr * ";
}

char * processArray(GenericNode * gn){
    if(gn == NULL) return NULL;

    char * openB = "{";
    char * closeB = "};"; 
    char * currentValue;
    int type;

    char * buffer;

    // Gets the numlist.
    NodeList * numList = gn->children->current->children;


    //Just for the first value
    type = determineVarType(numList->current);
    currentValue = numList->current->value;
    buffer = malloc(1 + strlen(openB) + strlen(currentValue));
    sprintf(buffer, "%s%s", openB, currentValue);

    numList = numList->next;
    
    while(numList != NULL){

        // If one of the elements its double, the whole array will be double
        if(determineVarType(numList->current) == DOUBLE_TYPE){
            type = DOUBLE_TYPE;
        }

        currentValue = numList->current->value;
        buffer = realloc(buffer, 1 + strlen(buffer) + strlen(", ") + strlen(currentValue));
        strcat(buffer, ", ");
        strcat(buffer, currentValue);
        
        numList = numList->next;
    }

    buffer = realloc(buffer, 1 + strlen(buffer) + strlen(closeB));
    strcat(buffer, closeB);

    if(type == INTEGER_TYPE){
        gn->info.varType = INTEGER_ARRAY_TYPE; 
    }
    else{
        gn->info.varType = DOUBLE_ARRAY_TYPE;
    }

    return buffer;
    
}

/*
char * processArray(GenericNode * gn){

    if(gn == NULL) return NULL;

    char * intArrayAuxDec = "IntArray * intArray_";
    char * doubleArrayAuxDec = "DoubleArray * doubleArray_";
    char * intArrayAuxAssigment = " = malloc(sizeof(IntArray));\n";
    char * doubleArrayAuxAssigment = " = malloc(sizeof(DoubleArray));\n";

    char * intArrayAuxName = "intArray_";
    char * doubleArrayAuxName = "doubleArray_";

    //TODO: make malloc dynamic with realloc.
    char * intArrayAuxInit = "->arr = malloc(sizeof(int));\n";
    char * doubleArrayAuxInit="->arr = malloc(sizeof(double)*100);\n";

    char * arrayAuxSetSize = "->size = ";
    char * arrayAuxAppend1= "->arr[";
    char * arrayAuxAppend2= "] = ";
    char * endLine= ";\n";

    char * buffer;
    int count = 0;
    char countChar[50];

    // Gets the numlist.
    NodeList * numList = gn->children->current->children;
    
    //If the first element of the array is an int --> All the array has to be int.
    if(determineVarType(numList->current) == INTEGER_TYPE){

        // Save to the buffer the declaration of the IntArray
        buffer = malloc(1 + strlen(intArrayAuxDec) + strlen(intArrayAuxAssigment));
        sprintf(buffer, "%s%s", intArrayAuxDec, intArrayAuxAssigment);

        //Allocate Memory for the arr inside the intArray.
        buffer = realloc(buffer, 1 + strlen(buffer) + strlen(intArrayAuxName) + strlen(intArrayAuxInit));
        strcat(buffer, intArrayAuxName);
        strcat(buffer, intArrayAuxInit);

        while(numList != NULL){
            if(determineVarType(numList->current) == INTEGER_TYPE){
                //Convert the count to char to index it on the buffer.
                sprintf(countChar, "%d", count);

                //Add the next number.
                buffer = realloc(buffer,1+strlen(buffer)+strlen(intArrayAuxName)+strlen(arrayAuxAppend1)+strlen(countChar)+strlen(arrayAuxAppend2)+strlen(numList->current->value)+strlen(endLine));
                strcat(buffer, intArrayAuxName);
                strcat(buffer, arrayAuxAppend1);
                strcat(buffer, countChar);
                strcat(buffer, arrayAuxAppend2);
                strcat(buffer, numList->current->value);
                strcat(buffer, endLine);
            }
            else{ 
                // TODO: ERROR
            }

            count++;
            numList = numList->next;
        }

        sprintf(countChar, "%d", count);

        // Assign the size to the IntArray
        buffer = realloc(buffer, 1 + strlen(buffer) +strlen(intArrayAuxName) +strlen(arrayAuxSetSize)+strlen(countChar)+strlen(endLine));
        strcat(buffer, intArrayAuxName);
        strcat(buffer, arrayAuxSetSize);
        strcat(buffer, countChar);
        strcat(buffer, endLine);
        gn->info.varType = INTEGER_ARRAY_TYPE;
    }
    //If the first element of the array is an double--> All the array has to be double
    else if(determineVarType(numList->current) == DOUBLE_TYPE){

        // Save to the buffer the declaration of the DoubleArray
        buffer = malloc(1 + strlen(doubleArrayAuxDec) + strlen(doubleArrayAuxAssigment));
        sprintf(buffer, "%s%s", doubleArrayAuxDec, doubleArrayAuxAssigment);

        //Allocate Memory for the arr inside the intArray.
        buffer = realloc(buffer, 1 + strlen(buffer) + strlen(doubleArrayAuxName) + strlen(doubleArrayAuxInit));
        strcat(buffer, doubleArrayAuxName);
        strcat(buffer, doubleArrayAuxInit);

        while(numList != NULL){
            if(determineVarType(numList->current) == DOUBLE_TYPE){
                //Convert the count to char to index it on the buffer.
                sprintf(countChar, "%d", count);

                //Add the next number.
                buffer = realloc(buffer,1+strlen(buffer)+strlen(doubleArrayAuxName)+strlen(arrayAuxAppend1)+strlen(countChar)+strlen(arrayAuxAppend2)+strlen(numList->current->value)+strlen(endLine));
                strcat(buffer, doubleArrayAuxName);
                strcat(buffer, arrayAuxAppend1);
                strcat(buffer, countChar);
                strcat(buffer, arrayAuxAppend2);
                strcat(buffer, numList->current->value);
                strcat(buffer, endLine);
            }
            else{ 
                // TODO: ERROR
            }

            count++;
            numList = numList->next;
        }

        sprintf(countChar, "%d", count);

        // Assign the size to the doubleArray
        buffer = realloc(buffer, 1 + strlen(buffer) +strlen(doubleArrayAuxName) +strlen(arrayAuxSetSize)+strlen(countChar)+strlen(endLine));
        strcat(buffer, doubleArrayAuxName);
        strcat(buffer, arrayAuxSetSize);
        strcat(buffer, countChar);
        strcat(buffer, endLine);
        gn->info.varType = DOUBLE_ARRAY_TYPE;
    }
    else{
        // TODO: ERROR
    }

    return buffer;
    
}

*/
