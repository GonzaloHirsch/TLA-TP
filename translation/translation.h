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
    ERROR_INVALID_OPERATION_TYPES,
    ERROR_UNDEFINED_VARIABLE,
    ERROR_INCOMPATIBLE_ASSIGNMENT,
    ERROR_UNASSIGNED_VARIABLE,
    ERROR_DUPLICATED_VARIABLE,
} CompilationErrors;

typedef struct FunctionDeclaration {
    char * code;
} FunctionDeclaration;

typedef struct FunctionDeclarations_ {
    struct FunctionDeclaration * functions;
    int count;
} FunctionDeclarations_;

typedef struct FunctionDeclarations_ * FunctionDeclarations;

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
char * getFunctionDeclarations();
char *translate(GenericNode *gn);
char *translate_program(GenericNode *gn, void (*error_fun)(GenericNode **, char *));

extern CompilationErrors compilationError;
extern FunctionDeclarations functionDeclarations;

#endif