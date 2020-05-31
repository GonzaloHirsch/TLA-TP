#include "node.h"

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