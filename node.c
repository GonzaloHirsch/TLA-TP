#include "node.h"

const char * getNodeTypeString (NodeType type);
// GenericNode * newGenericNodeAux(NodeList * hyperStatements) {
//     GenericNode * epn = malloc(sizeof(GenericNode));
//     epn -> info.type = NODE_ENTRYPOINT;
//     epn -> hyperstatements = hyperStatements;
//     return epn;
// }

GenericNode * newGenericNodeWithChildren(NodeType type, char * value, int childrenCount, ...) {
    va_list childrenList;
    GenericNode * createdNode = malloc(sizeof(GenericNode));
    createdNode->info.type = type;
    
    va_start(childrenList, childrenCount);
    createdNode->children = createNodeList(va_arg(childrenList, GenericNode *));
    int i = 1;
    for (NodeList * it = createdNode->children; i < childrenCount; i++) {
        it->next = createNodeList(va_arg(childrenList, GenericNode *));
        it = it->next;
    }
    va_end(childrenList);

    if(value != 0){
        createdNode->value = malloc(strlen(value) * sizeof(char));
        strcpy(createdNode->value, value);
    }
    else{
        createdNode->value = 0;
    }
    
    return createdNode;
}

NodeList * createNodeList(GenericNode * node) {
    NodeList * nl = malloc(sizeof(NodeList));
    nl -> info.type = NODE_LIST;
    nl -> current = node;
    nl -> next = NULL;
    return nl;
}

NodeList * addToNodeList(NodeList * nodeList, GenericNode * node) {

    NodeList * nl = nodeList;
    while (nl->next != NULL)
        nl = nl->next;
    nl->next = createNodeList(node);
    return nodeList;
}

NodeList * prependToNodeList(NodeList * nodeList, GenericNode * node) {
    NodeList * nl = createNodeList(node);
    nl->next = nodeList;
    return nl;
}


GenericNode * newGenericNode(NodeType type, char * value) {
    GenericNode * gn = malloc(sizeof(GenericNode));
    gn->info.type = type;
    if(value != 0){
        gn->value = malloc(strlen(value) * sizeof(char));
        strcpy(gn->value, value);
    }
    else{
        gn->value = 0;
    }
    return gn;
}

void printGenericNode(GenericNode * gn, int tabs) {

    for (int i = 0; i < tabs; i++)
        printf("  ");
    printf("%s %s\n", getNodeTypeString(gn->info.type), gn->value);
    if (gn->children != NULL) {
        printNodeList(gn->children, tabs + 1);
    }
}

void printNodeList (NodeList * nl, int tabs) {
    if (nl == NULL)
        return;
    printGenericNode(nl->current, tabs);
    printNodeList(nl->next, tabs);
}

void freeGenericNode (GenericNode * gn) {
    if (gn->children != NULL){
        freeNodeList(gn->children);
    }
    free(gn);
    printf("Freed node\n");
}

void freeNodeList (NodeList * nl) {
    if (nl == NULL)
        return;
    freeGenericNode(nl->current);
    freeNodeList(nl->next);
}

const char * getNodeTypeString (NodeType type) {
    switch (type){
        case NODE_LIST:
            return "node_list";
            break;
        case NODE_FUNCTIONS:
            return "node_functions";
            break;
        case NODE_ENTRYPOINT:  
            return "NODE_ENTRYPOINT";
            break;
        case NODE_IFSENTENCE:
            return "NODE_IFSENTENCE";
            break;
        case NODE_IFSENTENCE_ELSE:
            return "NODE_IFSENTENCE_ELSE";
            break;
        case NODE_ELSETRAIN:
            return "NODE_ELSETRAIN";
            break;
        case NODE_STATEMENT:
            return "NODE_STATEMENT";
            break;
        case NODE_VARDECLARATION:
            return "NODE_VARDECLARATION";
            break;
        case NODE_VARDECLASSIGNMENT:
            return "NODE_VARDECLASSIGNMENT";
            break;
        case NODE_FOREACH:
            return "NODE_FOREACH";
            break;
        case NODE_FOREACHBODY:
            return "NODE_FOREACHBODY";
            break;
        case NODE_BLOCK:
            return "NODE_BLOCK";
            break;
        case NODE_FUNBLOCK:
            return "NODE_FUNBLOCK";
            break;
        case NODE_ASSIGNMENT:
            return "NODE_ASSIGNMENT";
            break;
        case NODE_INT:
            return "NODE_INT";
            break;
        case NODE_STR:
            return "NODE_STR";
            break;
        case NODE_DOUBLE:
            return "NODE_DOUBLE";
            break;
        case NODE_VARIABLE:
            return "NODE_VARIABLE";
            break;
        case NODE_LITERAL:
            return "NODE_LITERAL";
            break;        
        case NODE_HYPERSTATEMENTS:
            return "NODE_HYPERSTATEMENTS";
            break;        
        case NODE_HYPERSTATEMENT:
            return "NODE_HYPERSTATEMENT";
            break;
        case NODE_INBLOCKSTATEMENTS:
            return "NODE_INBLOCKSTATEMENTS";
            break;
        case NODE_WHILE:
            return "NODE_WHILE";
            break;

        case NODE_G_EXPRESSION:
            return "NODE_G_EXPRESSION";
            break;

        case NODE_EXPRESSION:
            return "NODE_EXPRESSION";
            break;

        case NODE_G_OPERATION:
            return "NODE_G_OPERATION";
            break;
        case NODE_OPERATION:
            return "NODE_OPERATION";
            break;


        default:
            return "DEFAULT";
            break;
    }
}