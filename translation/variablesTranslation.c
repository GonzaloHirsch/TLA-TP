#include "variablesTranslation.h"

char * processVariable(GenericNode * gn) {
    printf("variable with value %s\n", gn->value);
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
