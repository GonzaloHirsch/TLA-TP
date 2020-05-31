#ifndef __NODE2_H__
#define __NODE2_H__
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
    
    NODE_ENTRYPOINT,
    NODE_HYPERSTATEMENT,
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

// Information about the node itself
typedef struct Node {
    NodeType type;
} Node;

// List of nodes
typedef struct NodeList {
    Node self;                  // Information about the type of node
    GenericNode * current;              // The current node with information
    struct NodeList * next;                // The next node on the list
} NodeList;

// This is used so as to enable polymorphism and reduce
// code size

typedef struct GenericNode {
    Node self;
} GenericNode;

typedef struct EntryPointNode {
    Node self;
    char testString[240];
    NodeList * hyperstatements;
} EntryPointNode;

typedef struct HyperStatementsNode {
    Node self;
    char testString[240];
    
} HyperStatementsNode;

// Node for a functions section
typedef struct FunctionsNode {
    Node self;                  // Information about the type of node
    NodeList * functions;       // List of functions declared
} FunctionsNode;

EntryPointNode * newEntryPointNode(NodeList * hyperStatements);
void freeEntryPointNode(EntryPointNode * entryPointNode);
createNodeList(GenericNode * node);
addToNodeList(NodeList * nodeList, GenericNode * node);
#endif