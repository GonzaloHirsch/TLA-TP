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

void freeEntryPointNode (EntryPointNode * epn) {
    if (epn->hyperstatements != NULL){
        free(epn->hyperstatements);
    }
    free(epn);
}