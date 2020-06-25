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
#include "./foreachTranslation.h"
#define EXIT_FAILURE_ -1

typedef enum CompilationErrors
{
    ERROR_NO_ERROR,
    ERROR_GENERIC,
    ERROR_INVALID_OPERATION_TYPES
} CompilationErrors;

//----------INTERNAL FUNCTIONS---------------------------
char *processStamentListNode(GenericNode *gn);
char *processWhileNode(GenericNode *gn);
char *process(GenericNode *gn);
char *processEntrypointNode(GenericNode *gn);
char *processBlock(GenericNode *gn);
char *processAssignment(GenericNode *gn);
char *processLeaf(GenericNode *gn);
char *processNodeList(NodeList *nl);
char *processInBlockStatements(GenericNode *gn);
char *processInBlockStatement(GenericNode *gn);
char *processHyperStatement(GenericNode *gn);
char *processHyperStatements(GenericNode *gn);
char *processPrint(GenericNode *);

VarType determineVarType(GenericNode *gn);

//----------------------------------------------------------

char *getHeadersAndFunctions();
char *translate(GenericNode *gn);
char *translate_program(GenericNode *gn, void (*error_fun)(GenericNode **, char *));

extern CompilationErrors compilationError;

#endif