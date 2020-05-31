#include "node2.h"

Node * newNode(NodeType type) {
    Node * node = malloc(sizeof(Node));
    node -> type = type;
    return node;
}

EntryPointNode * newEntryPointNode(NodeList * hyperStatements) {
    EntryPointNode * epn = malloc(sizeof(EntryPointNode));
    epn -> self.type = NODE_ENTRYPOINT;
    epn -> hyperstatements = hyperStatements;
    return epn;
}

NodeList * createNodeList(GenericNode * node) {
    NodeList * nl = malloc(sizeof(NodeList));
    nl -> self.type = NODE_LIST;
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

// For test purposes only

GenericNode * newGenericNode(NodeType type) {
    GenericNode * gn = malloc(sizeof(GenericNode));
    gn->self.type = type;
    return gn;
}

void freeEntryPointNode (EntryPointNode * epn) {
    if (epn->hyperstatements != NULL){
        // free(epn->hyperstatements);
    }
    free(epn);
}