#ifndef __NODE_H__
#define __NODE_H__
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "symboltable.h"
#define LENGTH 5000
#define MAX_CONCAT 5

typedef enum {
    NODE_LIST,
    NODE_FUNCTIONS,
    NODE_FUNCTION_DECLARATION,
    NODE_FUNCTION_CALL,
    NODE_VARIABLE,
    NODE_CONSTANT,
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_BLOCK,
    NODE_WHILE,
    NODE_IF,
    NODE_PRINT,
    NODE_MAIN,
    
    NODE_RETURN,
    NODE_IF,
    NODE_VARIABLE,
    NODE_CONSTANT
} NodeType;

// Information about the node itself
typedef struct Node {
    NodeType type;
} Node;

// List of nodes
typedef struct NodeList {
    Node self;                  // Information about the type of node
    Node * actual;              // The actual node with information
    Node * next;                // The next node on the list
} NodeList;

// Node for a functions section
typedef struct FunctionsNode {
    Node self;                  // Information about the type of node
    NodeList * functions;       // List of functions declared
} FunctionsNode;

typedef struct FunctionDefinitionNode {
    Node self;                  //
    NodeList * params;
    Node * block;
    Node * name;
} FunctionDefinitionNode;

typedef struct FunctionCallNode {
    Node self;
    Node * name;
    NodeList * params;
} FunctionCallNode;

typedef struct VariableNode {
    Node self;
    char * name;
} VariableNode;

typedef struct ConstantNode {
    Node self;
    VarType type;
    void * value;
} ConstantNode;

typedef struct BinaryOperationNode {
    Node self;
    Node * left;                // Left side of operation
    Node * right;               // Right side of operation
    char * op;                  // Operator for the operation
} BinaryOperationNode;

typedef struct UnaryOperationNode {
    Node self;
    Node * expression;                // Expression to be operated on
    char * op;                  // Operator for the expression
} UnaryOperationNode;

typedef struct BlockNode {
    Node self;
    NodeList * statement;
} BlockNode;

typedef struct WhileNode {
    Node self;
    NodeList * statements;
    Node * expression;
    Node * ret;
} WhileNode;

typedef struct IfNode {
    Node self;
    Node * ifExpression;
    Node * ifBlock;
    Node * elseIfExpression;
    Node * elseIfBlock;
} IfNode;

typedef struct PrintNode {
    Node self;
    Node * expression;
} PrintNode;

typedef struct MainNode {
    Node self;
    NodeList * statements;
} MainNode;

typedef struct StatementNode {
    Node self;
    Node * statement;
} StatementNode;

typedef struct symvar{
    char name[32];
    VarType type;
    void * value;
} symvartype;

char * c_string(char *a1, char * a2, char * a3, char *a4, char *a5);

char * dotProduct(int ** a,int ** b);


#endif