#ifndef _IF_TRANSLATION_H
#define _IF_TRANSLATION_H

#include "../node.h"
#include "translation.h"

char * processIf(GenericNode * gn);
char * processIfElse(GenericNode * gn);
char * processElseTrain(GenericNode * gn);

#endif