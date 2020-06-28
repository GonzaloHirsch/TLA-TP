#include "node.h"

const char *getNodeTypeString(NodeType type);
// GenericNode * newGenericNodeAux(NodeList * hyperStatements) {
//     GenericNode * epn = malloc(sizeof(GenericNode));
//     epn -> info.type = NODE_ENTRYPOINT;
//     epn -> hyperstatements = hyperStatements;
//     return epn;
// }

GenericNode *newGenericNodeWithChildren(NodeType type, char *value, int line, int childrenCount, ...)
{
    va_list childrenList;
    GenericNode *createdNode = malloc(sizeof(GenericNode));
    createdNode->info.type = type;
    createdNode->info.line = line;
    createdNode->info.isMeta = 0;

    va_start(childrenList, childrenCount);
    createdNode->children = createNodeList(va_arg(childrenList, GenericNode *), line);
    int i = 1;
    for (NodeList *it = createdNode->children; i < childrenCount; i++)
    {
        it->next = createNodeList(va_arg(childrenList, GenericNode *), line);
        it = it->next;
    }
    va_end(childrenList);

    if (value != 0)
    {
        createdNode->value = malloc(strlen(value) + 1);
        strcpy(createdNode->value, value);
    }
    else
    {
        createdNode->value = 0;
    }

    return createdNode;
}

NodeList *createNodeList(GenericNode *node, int line)
{
    NodeList *nl = malloc(sizeof(NodeList));
    nl->info.type = NODE_LIST;
    nl->info.line = line;
    nl->current = node;
    nl->next = NULL;
    return nl;
}

NodeList *addToNodeList(NodeList *nodeList, GenericNode *node)
{

    NodeList *nl = nodeList;
    while (nl->next != NULL)
        nl = nl->next;
    nl->next = createNodeList(node, nl->info.line);
    return nodeList;
}

NodeList *prependToNodeList(NodeList *nodeList, GenericNode *node)
{
    NodeList *nl = createNodeList(node, nl->info.line);
    nl->next = nodeList;
    return nl;
}

GenericNode *newGenericNode(NodeType type, char *value, int line)
{
    GenericNode *gn = malloc(sizeof(GenericNode));
    gn->info.type = type;
    gn->info.line = line;
    gn->info.isMeta = 0;
    if (value != 0)
    {
        gn->value = malloc(strlen(value) + 1);
        strcpy(gn->value, value);
    }
    else
    {
        gn->value = 0;
    }
    return gn;
}

void printGenericNode(GenericNode *gn, int tabs)
{

    for (int i = 0; i < tabs; i++)
        printf("  ");
    printf("%s %s\n", getNodeTypeString(gn->info.type), gn->value);
    if (gn->children != NULL)
    {
        printNodeList(gn->children, tabs + 1);
    }
}

void changeDescendantVarType(GenericNode *gn, char *varName, VarType targetVarType, int isMeta)
{
    if (gn->info.type == NODE_VARIABLE_REF && strcmp(gn->value, varName) == 0)
    {
        gn->info.varType = targetVarType;
        if (isMeta)
            gn->info.isMeta = isMeta;
    }
    else
        changeDescendantVarTypeForList(gn->children, varName, targetVarType, isMeta);
}

void changeDescendantVarTypeForList(NodeList *nl, char *varName, VarType targetVarType, int isMeta)
{
    if (nl == NULL)
        return;
    changeDescendantVarType(nl->current, varName, targetVarType, isMeta);
    changeDescendantVarTypeForList(nl->next, varName, targetVarType, isMeta);
}

int listHasDescendantOfType(NodeList *nl, NodeType nodeType)
{
    if (nl == NULL)
        return 0;
    return hasDescendantOfType(nl->current, nodeType) || listHasDescendantOfType(nl->next, nodeType);
}

int hasDescendantOfType(GenericNode *gn, NodeType nodeType)
{
    if (gn->info.type == nodeType)
        return 1;
    else
        return listHasDescendantOfType(gn->children, nodeType);
}

void printNodeList(NodeList *nl, int tabs)
{
    if (nl == NULL)
        return;
    printGenericNode(nl->current, tabs);
    printNodeList(nl->next, tabs);
}

void freeGenericNode(GenericNode *gn)
{
    if (gn == NULL)
        return;

    if (gn->children != NULL)
    {
        freeNodeList(gn->children);
    }
    free(gn);
    gn = NULL;
}

void freeNodeList(NodeList *nl)
{
    if (nl == NULL)
        return;
    freeGenericNode(nl->current);
    freeNodeList(nl->next);
    free(nl);
    nl = NULL;
}

const char *getNodeTypeString(NodeType type)
{
    switch (type)
    {
    case NODE_LIST:
        return "NODE_LIST";
        break;
    case NODE_FUNCTIONS:
        return "NODE_FUNCTIONS";
        break;
    case NODE_ENTRYPOINT:
        return "NODE_ENTRYPOINT";
        break;
    case NODE_HYPERSTATEMENT:
        return "NODE_HYPERSTATEMENT";
        break;
    case NODE_HYPERSTATEMENTS:
        return "NODE_HYPERSTATEMENTS";
        break;
    case NODE_INBLOCKSTATEMENTS:
        return "NODE_INBLOCKSTATEMENTS";
        break;
    case NODE_INBLOCKSTATEMENT:
        return "NODE_INBLOCKSTATEMENT";
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
    case NODE_WHILE:
        return "NODE_WHILE";
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
    case NODE_ASSIGNMENT:
        return "NODE_ASSIGNMENT";
        break;
    case NODE_LITERAL:
        return "NODE_LITERAL";
        break;
    case NODE_VARIABLE:
        return "NODE_VARIABLE";
        break;
    case NODE_VARIABLE_ASSIGNMENT:
        return "NODE_VARIABLE_ASSIGNMENT";
        break;
    case NODE_VARIABLE_REF:
        return "NODE_VARIABLE_REF";
        break;  
    case NODE_ARRAYLITERAL:
        return "NODE_ARRAYLITERAL";
        break;
    case NODE_STRING_LITERAL:
        return "NODE_STRING_LITERAL";
        break;
    case NODE_OPERATION:
        return "NODE_OPERATION";
        break;
    case NODE_G_OPERATION:
        return "NODE_G_OPERATION";
        break;
    case NODE_EXPRESSION:
        return "NODE_EXPRESSION";
        break;
    case NODE_G_EXPRESSION:
        return "NODE_G_EXPRESSION";
        break;
    case NODE_INT:
        return "NODE_INT";
        break;
    case NODE_DOUBLE:
        return "NODE_DOUBLE";
        break;
    case NODE_STR:
        return "NODE_STR";
        break;
    case NODE_ARR_INT:
        return "NODE_ARR_INT";
        break;
    case NODE_ARR_DOUBLE:
        return "NODE_ARR_DOUBLE";
        break;
    case NODE_NUMLIST:
        return "NODE_NUMLIST";
        break;
    case NODE_PRINT:
        return "NODE_PRINT";
        break;
    case NODE_GET_INT:
        return "NODE_GET_INT";
        break;
    case NODE_GET_DOUBLE:
        return "NODE_GET_DOUBLE";
        break;
    case NODE_GET_STRING:
        return "NODE_GET_STRING";
        break;
    case NODE_ARRAY_ACCESS:
        return "NODE_ARRAY_ACCESS";
        break;
    case NODE_EXIT:
        return "NODE_EXIT";
        break;
    default:
        return "DEFAULT";
        break;
    }
}