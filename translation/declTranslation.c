#include "declTranslation.h"

char * processVarDeclaration(GenericNode * gn) {
    if(gn == NULL) return NULL;

    NodeList * nl = gn->children;
    char * type = translate(nl->current);
    if (type == NULL){
        printf("PROCESSVARDECLARATION FAIL ON TYPE");
        return NULL;
    }   

    nl = nl->next;
    char * var = translate(nl->current);
    if (var == NULL){
        printf("PROCESSVARDECLARATION FAIL ON VAR");
        //free(type)
        return NULL;
    }

    if (strcmp(type, "int") == 0){
        nl->current->info.varType = INTEGER_TYPE;
        symAddInt(nl->current->value);
    } else if (strcmp(type, "IntArr * ") == 0){
        nl->current->info.varType = INTEGER_ARRAY_TYPE;
        symAddIntArr(nl->current->value);
    } else if (strcmp(type, "str") == 0){
        nl->current->info.varType = STRING_TYPE;
        symAddString(nl->current->value);
    } else if (strcmp(type, "double") == 0){
        nl->current->info.varType = DOUBLE_TYPE;
        symAddDouble(nl->current->value);
    } else if (strcmp(type, "DoubleArr * ") == 0){
        nl->current->info.varType = DOUBLE_ARRAY_TYPE;
        symAddDoubleArr(nl->current->value);
    } else {
        // ERROR
    }

    char * numberLiteral = NULL;
    char * buffer;



    if (nl->next != NULL) {
        nl = nl->next;
        numberLiteral = translate(nl->current);
        buffer = malloc(strlen(type) + strlen(var) + strlen(numberLiteral) + 4 + 1); // 2 for brackets, 1 for space,1 for \n,  1 for \0
        sprintf(buffer, "%s %s[%s]\n", type, var, numberLiteral);
    }
    else {
        buffer = malloc(strlen(type) + strlen(var) + 1 + 1);
        sprintf(buffer, "%s %s\n", type, var);
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

    // Determining the type and inserting the variable, must be done before processing variable to get accourate type
    if (strcmp(type, "int") == 0){
        gn->info.varType = INTEGER_TYPE;
        symAddInt(nl->current->value);
    } else if (strcmp(type, "IntArr * ") == 0){
        gn->info.varType = INTEGER_ARRAY_TYPE;
        symAddIntArr(nl->current->value);
    } else if (strcmp(type, "str") == 0){
        gn->info.varType = STRING_TYPE;
        symAddString(nl->current->value);
    } else if (strcmp(type, "double") == 0){
        gn->info.varType = DOUBLE_TYPE;
        symAddDouble(nl->current->value);
    } else if (strcmp(type, "DoubleArr * ") == 0){
        gn->info.varType = DOUBLE_ARRAY_TYPE;
        symAddDoubleArr(nl->current->value);
    } else {
        // ERROR
    }

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
        // ERROR
        printf("ERROR\n;");
        return NULL;
    }
        
    return buffer;
}