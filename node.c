#include "node.h"

int mallocError(void * pointer){
    if(pointer == NULL){
        return 1;
    }
    return 0;
}


Node * initNode(NodeType type){
    Node * node = malloc(sizeof(Node *));
    if(mallocError(node)) {
        return NULL;
    }
    node->type = type;

}

void freeNode(Node * node){
    if(node != NULL){
        free(node);
    }
    
}


NodeList * initNodeList(Node info, Node * actual, Node * next){
    NodeList * nList = malloc(sizeof(NodeList *));
        if(mallocError(nList)) {
        return NULL;
    }

    nList->info = info;
    nList->actual = actual;
    nList-> next = next;

}

FunctionsNode * initFuncNode(Node info, NodeList * functions){
        FunctionsNode * funcList = malloc(sizeof(FunctionsNode *));
        if(mallocError(funcList)) {
        return NULL;
    }

    funcList ->info = info;
    funcList -> functions = functions;

    return funcList;
}



FunctionDefinitionNode * initFuncDefNode(Node info, NodeList * params, Node * block, Node * name){
    FunctionDefinitionNode * funcDef = malloc(sizeof(FunctionDefinitionNode *));
        if(mallocError(funcDef)) {
            return NULL;
         }
    funcDef -> info = info;
    funcDef -> params = params;
    funcDef -> block = block;
    funcDef -> name = name;

    return funcDef;
}


FunctionCallNode * initFuncCallNode(Node info, char * name, NodeList * params){
        FunctionCallNode * funcCall = malloc(sizeof(FunctionCallNode *));
        if(mallocError(funcCall)) {
            return NULL;
         }

        funcCall -> info = info;
        funcCall -> name = name;
        funcCall -> params = params;


        return funcCall;


}

VariableNode * initVarNode(Node info, char * name){
    VariableNode * varNode = malloc(sizeof(VariableNode *));
    if(mallocError(varNode)) {
        return NULL;
    }


    // have to update variables value
    varNode -> info = info;
    varNode -> name = name;

    return varNode;

}


ConstantNode * initConstNode(Node info, VarType type, void * value){
    //initialize constant depending on type later? constant needs type?
    ConstantNode * constNode = malloc(sizeof(ConstantNode *));
    if(mallocError(constNode)) {
        return NULL;
    }

    constNode -> info = info;
    constNode -> type = type;
    constNode -> value = value;

    return constNode;


}

BinaryOperationNode * initBinaryOperationNode(Node info, Node * left, Node * right, char * op){
    BinaryOperationNode * binOpNode = malloc(sizeof(BinaryOperationNode *));
    if(mallocError(binOpNode)) {
        return NULL;
    }

    binOpNode -> info = info;
    binOpNode -> left = left;
    binOpNode -> right = right;
    binOpNode -> op = op;

    return binOpNode;

}


UnaryOperationNode * initUnaryOperationNode(Node info, Node * expression, char * op){
    UnaryOperationNode * unOpNode = malloc(sizeof(UnaryOperationNode *));
    if(mallocError(unOpNode)) {
        return NULL;
    }

    unOpNode -> info = info;
    unOpNode -> expression = expression;
    unOpNode -> op = op;

    return unOpNode;

}

BlockNode * initBlockNode(Node info, NodeList * statement){
    BlockNode * blockNode = malloc(sizeof(BlockNode *));
    if(mallocError(blockNode)) {
        return NULL;
    }

    blockNode -> info = info;
    blockNode -> statement = statement;

    return blockNode;

}


WhileNode * initWhileNode(Node info, NodeList * statements, Node * expression, Node * ret){
    WhileNode * whileNode = malloc(sizeof(WhileNode *));
    if(mallocError(whileNode)) {
        return NULL;
    }

    whileNode -> info = info;
    whileNode -> statements = statements;
    whileNode -> expression = expression;
    whileNode -> ret = ret;

    return whileNode;

}

IfNode * initIfNode(Node info, Node * ifExpression, Node  * ifBlock, Node * elseIfExpression, Node * elseBlock ){
    IfNode * ifNode = malloc(sizeof(IfNode *));
    if(mallocError(ifNode)) {
        return NULL;
    }

    ifNode -> info = info;
    ifNode -> ifExpression = ifExpression;
    ifNode -> ifBlock = ifBlock;
    ifNode -> elseIfExpression = elseIfExpression;
    ifNode -> elseIfBlock = elseBlock;


    return ifNode;

}


PrintNode * initPrintNode(Node info, Node * expression){
    PrintNode * printNode = malloc(sizeof(PrintNode *));
    if(mallocError(printNode)) {
        return NULL;
    }  


    printNode -> info = info;
    printNode -> expression = expression;


    return printNode;

}

MainNode  * initMainNode(Node info, NodeList * statements){
    MainNode * mainNode = malloc(sizeof(MainNode *));
    if(mallocError(mainNode)) {
        return NULL;
    }  

    mainNode -> info = info;
    mainNode -> statements = statements;

    return mainNode;
    
}


StatementNode * initStatement(Node info, Node * statement){

    StatementNode * statementNode = malloc(sizeof(StatementNode *));
    if(mallocError(statementNode)) return NULL;

    statementNode -> info = info;
    statementNode -> statement = statementNode;

    return statementNode;
}



