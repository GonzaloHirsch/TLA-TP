#ifndef __TRANSLATION_H__
#define __TRANSLATION_H__

#include "../node.h"
#include <string.h>
#include <stdlib.h>
#include "./variablesTranslation.h"
#include "./declTranslation.h"
#include "./ifTranslation.h"

//----------INTERNAL FUNCTIONS---------------------------
char * processStamentListNode(GenericNode * gn);
char * processWhileNode(GenericNode * gn);
char * process(GenericNode * gn);
char * processEntrypointNode(GenericNode * gn);
char * processBlock(GenericNode * gn);
char * processAssignment(GenericNode * gn);
char * processLeaf(GenericNode * gn);
char * processGeneralExpression(GenericNode * gn);
char * processExpression(GenericNode * gn);


char * processInt(GenericNode * gn);
char * processInBlockStatements(GenericNode * gn);
char * processHyperStatement(GenericNode * gn);
char * processHyperStatements(GenericNode * gn);

//----------------------------------------------------------



char * translate(GenericNode * gn);

#endif