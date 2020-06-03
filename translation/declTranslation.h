#ifndef _DECL_TRANSLATION_H
#define _DECL_TRANSLATION_H

#include "../node.h"
#include "translation.h"
#include "symboltable.h"

char * processVarDeclaration(GenericNode * gn);
char * processVarDeclassignment(GenericNode * gn);

#endif