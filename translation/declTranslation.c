#include "declTranslation.h"

char *processVarDeclaration(GenericNode *gn)
{
    if (gn == NULL)
        return NULL;

    NodeList *nl = gn->children;
    GenericNode *typeNode = nl->current;
    char *type = translate(nl->current);
    if (type == NULL)
    {
        return NULL;
    }

    nl = nl->next;
    GenericNode *varNode = nl->current;
    char *var = translate(varNode);
    if (var == NULL)
    {
        //free(type)
        return NULL;
    }

    // Check if the already variable exists
    if (symLook(varNode->value) != NULL)
    {
        //free(type)
        //free(var)
        fprintf(stderr, "ERROR: Duplicate variable declaration");
        exit(EXIT_FAILURE_);
    }

    //If the variable doesn't exists, we add it based on the var type.
    symvartype *varAdded = symAdd(varNode->value, typeNode->info.varType);
    if (varAdded == NULL)
    {
        //free(type);
        //free(var);
        fprintf(stderr, "ERROR: Failure creating the variable");
        exit(EXIT_FAILURE_);
    }

    //Dont return anything: All declarations will be at the beginning.

    return NULL;
}

char *processVarDeclassignment(GenericNode *gn)
{
    if (gn == NULL)
        return NULL;

    char *buffer;
    NodeList *nl = gn->children;

    // Get the type
    GenericNode *typeNode = nl->current;
    char *type = translate(typeNode);
    if (type == NULL)
    {
        return NULL;
    }

    //Get the variable
    nl = nl->next;
    GenericNode *varNode = nl->current;

    char *var = translate(varNode);
    if (var == NULL)
    {
        //free(type);
        return NULL;
    }

    //Get the right value.
    nl = nl->next;
    GenericNode *valueNode = nl->current;
    char *value = translate(valueNode);
    if (value == NULL)
    {
        //free(type);
        //free(var);
        return NULL;
    }

    // Check if the variable already exists.
    if (symLook(varNode->value) != NULL)
    {
        //free(type);
        //free(var);
        //free(value);
        compilationError = ERROR_DUPLICATED_VARIABLE;
        return NULL;
    }
    //If the variable doesn't exists, we add it based on the var type.
    symvartype *varAdded = symAdd(varNode->value, typeNode->info.varType);
    if (varAdded == NULL)
    {
        //free(type);
        //free(var);
        fprintf(stderr, "ERROR: Failure creating the variable\n");
        exit(EXIT_FAILURE_);
    }

    // Variable is assigned
    symSetAssigned(varAdded);

    // Create the buffer depending on the varType.
    // The type of the typeNode has to match the type of the valueNode.
    if (typeNode->info.varType == INTEGER_ARRAY_TYPE && valueNode->info.varType == INTEGER_ARRAY_TYPE)
    {
        // This means its the value of an array function
        if (value[0] == '_')
        {
            char *intArrDec = "%s = %s;\n";
            buffer = malloc(1 + strlen(intArrDec) + strlen(var) + strlen(value) - 4);
            sprintf(buffer, intArrDec, var, value);
        }
        else
        {
            //Declaration was moved to the beginning of main --> dont do it here
            char *intArrDec = "int _%s[] = %s;\n"
                              "%s = malloc(sizeof(IntArr));\n"
                              "%s->arr = _%s;\n"
                              "%s->size = NELEMS(_%s);\n"
                              "%s->on_access = &_check_int_index;\n";
            buffer = malloc(1 + strlen(intArrDec) + 7 * strlen(var) + strlen(value) - 14);
            sprintf(buffer, intArrDec, var, value, var, var, var, var, var, var);
        }
    }
    else if ((typeNode->info.varType == DOUBLE_ARRAY_TYPE && valueNode->info.varType == DOUBLE_ARRAY_TYPE) || (typeNode->info.varType == DOUBLE_ARRAY_TYPE && valueNode->info.varType == INTEGER_ARRAY_TYPE))
    {
        // This means its the value of an array function
        if (value[0] == '_')
        {
            char *doubleArrDec = "%s = %s;\n";
            buffer = malloc(1 + strlen(doubleArrDec) + strlen(var) + strlen(value) - 4);
            sprintf(buffer, doubleArrDec, var, value);
        }
        else
        {
            char *doubleArrDec = "double _%s[] = %s;\n"
                                 "%s = malloc(sizeof(DoubleArr));\n"
                                 "%s->arr = _%s;\n"
                                 "%s->size = NELEMS(_%s);\n"
                                 "%s->on_access = &_check_double_index;\n";
            buffer = malloc(1 + strlen(doubleArrDec) + 7 * strlen(var) + strlen(value) - 14);
            sprintf(buffer, doubleArrDec, var, value, var, var, var, var, var, var);
        }
    }
    else if (typeNode->info.varType == DOUBLE_TYPE && (valueNode->info.varType == DOUBLE_TYPE || valueNode->info.varType == INTEGER_TYPE))
    {
        buffer = malloc(strlen(type) + strlen(var) + strlen(value) + strlen("=  ;\n") + 1);
        sprintf(buffer, "%s = %s;\n", var, value);
    }
    else if (typeNode->info.varType == valueNode->info.varType)
    {
        buffer = malloc(strlen(type) + strlen(var) + strlen(value) + strlen("=  ;\n") + 1);
        sprintf(buffer, "%s = %s;\n", var, value);
    }
    else
    {
        compilationError = ERROR_INCOMPATIBLE_ASSIGNMENT;
        return NULL;
    }

    return buffer;
}

char *getVarDeclarations()
{

    char *buffer = malloc(1);
    buffer[0] = 0x00;
    if (buffer == NULL)
    {
        exit(1);
    }

    symvartype *current;
    char *name, *type;
    int i = 0;
    do
    {
        current = symLookByIndex(i++);
        if (current != NULL)
        {
            name = current->name;
            switch (current->type)
            {
            case STRING_TYPE:
                type = "static char *";
                break;
            case INTEGER_TYPE:
                type = "static int";
                break;
            case DOUBLE_TYPE:
                type = "static double";
                break;
            case INTEGER_ARRAY_TYPE:
                type = "static IntArr *";
                break;
            case DOUBLE_ARRAY_TYPE:
                type = "static DoubleArr *";
                break;
            }

            buffer = realloc(buffer, 1 + strlen(" ;\n") + strlen(buffer) + strlen(name) + strlen(type));
            if (buffer == NULL)
            {
                exit(1);
            }
            strcat(buffer, type);
            strcat(buffer, " ");
            strcat(buffer, name);
            strcat(buffer, ";\n");
        }
    } while (current != NULL);

    return buffer;
}