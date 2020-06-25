#ifndef _VARIABLES_TRANSLATION_H
#define _VARIABLES_TRANSLATION_H

#include "../node.h"
#include "./translation.h"
#include "./symboltable.h"

char * processVariable(GenericNode * gn);
char * processAssignedVariable(GenericNode * gn);
char * processReferencedVariable(GenericNode * gn);
char * processDouble(GenericNode * gn);
char * processStr(GenericNode * gn);
char * processInt(GenericNode * gn);
char * processArrayTypeInt(GenericNode * gn);
char * processArrayTypeDouble(GenericNode * gn);
char * processArray(GenericNode * gn);

#endif