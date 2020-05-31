#ifndef __NODE2_H__
#define __NODE2_H__
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "symboltable.h"
#define LENGTH 5000
#define MAX_CONCAT 5   

typedef enum {
    NODE_LIST,
    NODE_FUNCTIONS,
    
    NODE_ENTRYPOINT,
    NODE_HYPERSTATEMENT,
    NODE_HYPERSTATEMENTS,
    NODE_INBLOCKSTATEMENTS,
    NODE_INBLOCKSTATEMENT,
    NODE_IFSENTENCE,
    NODE_ELSETRAIN,
    NODE_WHILE,
    NODE_STATEMENT,
    NODE_VARDECLARATION,
    NODE_VARDECLASSIGNMENT,
    NODE_FOREACH,
    NODE_FOREACHBODY,
    NODE_BLOCK,
    NODE_ASSIGNMENT,
    NODE_LITERAL
} NodeType;

// Information about the node itinfo
typedef struct NodeInfo {
    NodeType type;
} NodeInfo;

// List of nodes
typedef struct NodeList {
    NodeInfo info;                  // Information about the type of node
    struct GenericNode * current;              // The current node with information
    struct NodeList * next;                // The next node on the list
} NodeList;

// This is used so as to enable polymorphism and reduce
// code size

typedef struct GenericNode {
    NodeInfo info;
    char testString[240];
    struct GenericNode * parent;
    NodeList * children;
} GenericNode;

// Node for a functions section
typedef struct FunctionsNode {
    NodeInfo info;                  // Information about the type of node
    NodeList * functions;       // List of functions declared
} FunctionsNode;

NodeList * createNodeList(GenericNode * node);
NodeList * addToNodeList(NodeList * nodeList, GenericNode * node);

GenericNode * newGenericNode(NodeType type);
GenericNode * newGenericNodeWithChildren(NodeType type, int childrenCound, ...);

void freeGenericNode(GenericNode * GenericNode);
void freeNodeList (NodeList * nl);

#endif