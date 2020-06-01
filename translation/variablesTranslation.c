#include "variablesTranslation.h"

char * processVariable(GenericNode * gn) {
    printf("variable with value %s\n", gn->value);
    return gn->value;
}
char * processDouble(GenericNode * gn) {
    printf("double with value %s\n", gn->value);
    return gn->value;
}
char * processStr(GenericNode * gn) {
    printf("str with value %s\n", gn->value);
    return gn->value;
}

char * processInt(GenericNode * gn) {
    printf("Int with value %s\n", gn->value);
    return gn->value;
}
