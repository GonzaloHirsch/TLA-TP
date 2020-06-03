#ifndef __TRANSLATION_H__
#define __TRANSLATION_H__

#include "../node.h"
#include <string.h>
#include <stdlib.h>
#include "./variablesTranslation.h"
#include "./declTranslation.h"
#include "./ifTranslation.h"
#include "./statementTranslation.h"
#include "./expressionTranslation.h"
#include "./opTranslation.h"

//----------INTERNAL FUNCTIONS---------------------------
char * processStamentListNode(GenericNode * gn);
char * processWhileNode(GenericNode * gn);
char * process(GenericNode * gn);
char * processEntrypointNode(GenericNode * gn);
char * processBlock(GenericNode * gn);
char * processAssignment(GenericNode * gn);
char * processLeaf(GenericNode * gn);
char * processNodeList(NodeList * nl);
char * processInBlockStatements(GenericNode * gn);
char * processInBlockStatement(GenericNode * gn);   
char * processHyperStatement(GenericNode * gn);
char * processHyperStatements(GenericNode * gn);
char * processPrint(GenericNode *);

VarType determineVarType(GenericNode * gn);

//----------------------------------------------------------

char * getHeadersAndFunctions();
char * translate(GenericNode * gn);

#endif