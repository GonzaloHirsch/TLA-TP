#include "declTranslation.h"

char * processVarDeclaration(GenericNode * gn) {
    if(gn == NULL) return NULL;

    NodeList * nl = gn->children;
    GenericNode * typeNode = nl->current;
    char * type = translate(nl->current);
    if (type == NULL){
        return NULL;
    }   

    nl = nl->next;
    GenericNode * varNode = nl->current;
    char * var = translate(varNode);
    if (var == NULL){
        //free(type)
        return NULL;
    }

    // Check if the already variable exists
    if(symLook(varNode->value) != NULL){
        //free(type)
        //free(var)
        fprintf(stderr, "ERROR: Duplicate variable declaration");
        exit(EXIT_FAILURE_);
    }

    //If the variable doesn't exists, we add it based on the var type.
    symvartype * varAdded = symAdd(varNode->value, typeNode->info.varType);
    if(varAdded == NULL){
        //free(type);
        //free(var);
        fprintf(stderr, "ERROR: Failure creating the variable");
        exit(EXIT_FAILURE_);
    }

    char * numberLiteral = NULL;
    char * buffer;

    if (nl->next != NULL) {
        nl = nl->next;
        numberLiteral = translate(nl->current);
        buffer = malloc(strlen(type) + strlen(var) + strlen(numberLiteral) +strlen(" []") + 1); // 2 for brackets, 1 for space,1 for \n,  1 for \0
        sprintf(buffer, "%s %s[%s]", type, var, numberLiteral);
    }
    else {
        buffer = malloc(strlen(type) + strlen(var) + strlen(" ") + 1);
        sprintf(buffer, "%s %s", type, var);
    }

    return buffer;
}


char * processVarDeclassignment(GenericNode * gn) {
    if(gn == NULL) return NULL;

    char * buffer;
    NodeList * nl = gn->children;

    // Get the type
    GenericNode * typeNode = nl->current;
    char * type = translate(typeNode);
    if(type == NULL){
        return NULL;
    }

    //Get the variable
    nl = nl->next;
    GenericNode * varNode = nl->current;

    char * var = translate(varNode);
    if(var == NULL){
        //free(type);
        return NULL;
    }

    //Get the right value.
    nl = nl->next;
    GenericNode * valueNode = nl->current;
    char * value = translate(valueNode);
    if(value == NULL){
        //free(type);
        //free(var);
        return NULL;
    }

    // Check if the variable already exists.
    if(symLook(varNode->value) != NULL){
        //free(type);
        //free(var);
        //free(value);
        fprintf(stderr, "ERROR: Duplicate variable declaration");
        exit(EXIT_FAILURE_);
    }
    //If the variable doesn't exists, we add it based on the var type.
    symvartype * varAdded = symAdd(varNode->value, typeNode->info.varType);
    if(varAdded == NULL){
        //free(type);
        //free(var);
        fprintf(stderr, "ERROR: Failure creating the variable");
        exit(EXIT_FAILURE_);
    }


    // Create the buffer depending on the varType.
    // The type of the typeNode has to match the type of the valueNode.
    if(typeNode->info.varType == INTEGER_ARRAY_TYPE && valueNode->info.varType == INTEGER_ARRAY_TYPE){
        // This means its the value of an array function
        if (value[0] == '_'){
            char * intArrDec = "IntArr * %s = %s;\n";
            buffer = malloc(1 + strlen(intArrDec) + strlen(var) +strlen(value) - 4 );
            sprintf(buffer, intArrDec, var, value);
        } else {
            char * intArrDec =  "int _%s[] = %s;\n"
                                "IntArr * %s = malloc(sizeof(IntArr));\n"
                                "%s->arr = _%s;\n"
                                "%s->size = NELEMS(_%s);\n";
            buffer = malloc(1 + strlen(intArrDec) + 6*strlen(var) +strlen(value) - 14 );
            sprintf(buffer, intArrDec, var, value, var, var, var, var,var);
        }
    }
    else if(typeNode->info.varType == DOUBLE_ARRAY_TYPE && valueNode->info.varType == DOUBLE_ARRAY_TYPE){
        // This means its the value of an array function
        if (value[0] == '_'){
            char * doubleArrDec = "DoubleArr * %s = %s;\n";
            buffer = malloc(1 + strlen(doubleArrDec) + strlen(var) +strlen(value) -4);
            sprintf(buffer, doubleArrDec, var, value);
        } else {
            char * doubleArrDec =   "double _%s[] = %s;\n"
                                    "DoubleArr * %s = malloc(sizeof(DoubleArr));\n"
                                    "%s->arr = _%s;\n"
                                    "%s->size = NELEMS(_%s);\n";
            buffer = malloc(1 + strlen(doubleArrDec) + 6*strlen(var) +strlen(value) -14 );
            sprintf(buffer, doubleArrDec, var, value, var, var, var, var,var);
        }
    }
    else if(typeNode->info.varType == valueNode->info.varType){
        buffer = malloc(strlen(type) + strlen(var) + strlen(value) + strlen(" =  ") + 1);
        sprintf(buffer, "%s %s = %s", type, var, value);
    }
    else{
        fprintf(stderr, "ERROR: Duplicate variable declaration");
        exit(EXIT_FAILURE_);
    }
        
    return buffer;
}