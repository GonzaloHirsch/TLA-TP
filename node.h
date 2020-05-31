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

// Information about the node itinfo
typedef struct Node {
    NodeType type;
} Node;

// List of nodes
typedef struct NodeList {
    Node info;                  // Information about the type of node
    Node * actual;              // The actual node with information
    Node * next;                // The next node on the list
} NodeList;

// Node for a functions section
typedef struct FunctionsNode {
    Node info;                  // Information about the type of node
    NodeList * functions;       // List of functions declared
} FunctionsNode;

typedef struct FunctionDefinitionNode {
    Node info;                  //
    NodeList * params;
    Node * block;
    Node * name;
} FunctionDefinitionNode;

typedef struct FunctionCallNode {
    Node info;
    char * name;
    NodeList * params;
} FunctionCallNode;

typedef struct VariableNode {
    Node info;
    char * name;
} VariableNode;

typedef struct ConstantNode {
    Node info;
    VarType type;
    void * value;
} ConstantNode;

typedef struct BinaryOperationNode {
    Node info;
    Node * left;                // Left side of operation
    Node * right;               // Right side of operation
    char * op;                  // Operator for the operation
} BinaryOperationNode;

typedef struct UnaryOperationNode {
    Node info;
    Node * expression;                // Expression to be operated on
    char * op;                  // Operator for the expression
} UnaryOperationNode;

typedef struct BlockNode {
    Node info;
    NodeList * statement;
} BlockNode;

typedef struct WhileNode {
    Node info;
    NodeList * statements;
    Node * expression;
    Node * ret;
} WhileNode;

typedef struct IfNode {  //how to get the values of each node?
    Node info;
    Node * ifExpression;
    Node * ifBlock;
    Node * elseIfExpression;
    Node * elseIfBlock;
} IfNode;

typedef struct PrintNode {
    Node info;
    Node * expression;
} PrintNode;

typedef struct MainNode {
    Node info;
    NodeList * statements;
} MainNode;

typedef struct StatementNode {
    Node info;
    Node * statement;
} StatementNode;

typedef struct symvar{
    char name[32];
    VarType type;
    void * value;
} symvartype;

char * c_string(char *a1, char * a2, char * a3, char *a4, char *a5);

char * dotProduct(int ** a,int ** b);

Node * initNode(NodeType type);
void freeNode(Node * node);
NodeList * initNodeList(Node info, Node * actual, Node * next);
FunctionsNode * initFuncNode(Node info, NodeList * functions);
FunctionDefinitionNode * initFuncDefNode(Node info, NodeList * params, Node * block, Node * name);
FunctionCallNode * initFuncCallNode(Node info, char * name, NodeList * params);
VariableNode * initVarNode(Node info, char * name);
ConstantNode * initConstNode(Node info, VarType type, void * value);
BinaryOperationNode * initBinaryOperationNode(Node info, Node * left, Node * right, char * op);
UnaryOperationNode * initUnaryOperationNode(Node info, Node * expression, char * op);
BlockNode * initBlockNode(Node info, NodeList * statement);
WhileNode * initWhileNode(Node info, NodeList * statements, Node * expression, Node * ret);
PrintNode * initPrintNode(Node info, Node * expression);
MainNode  * initMainNode(Node info, NodeList * statements);
StatementNode * initStatement(Node info, Node * statement);

#endif