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


NodeList * initNodeList(Node self, Node * actual, Node * next){
    NodeList * nList = malloc(sizeof(NodeList *));
        if(mallocError(nList)) {
        return NULL;
    }

    nList->self = self;
    nList->actual = actual;
    nList-> next = next;

}

FunctionsNode * initFuncNode(Node self, NodeList * functions){
        FunctionsNode * funcList = malloc(sizeof(FunctionsNode *));
        if(mallocError(funcList)) {
        return NULL;
    }

    funcList ->self = self;
    funcList -> functions = functions;

    return funcList;
}



FunctionDefinitionNode * initFuncDefNode(Node self, NodeList * params, Node * block, Node * name){
    FunctionDefinitionNode * funcDef = malloc(sizeof(FunctionDefinitionNode *));
        if(mallocError(funcDef)) {
            return NULL;
         }
    funcDef -> self = self;
    funcDef -> params = params;
    funcDef -> block = block;
    funcDef -> name = name;

    return funcDef;
}


FunctionCallNode * initFuncCallNode(Node self, char * name, NodeList * params){
        FunctionCallNode * funcCall = malloc(sizeof(FunctionCallNode *));
        if(mallocError(funcCall)) {
            return NULL;
         }

        funcCall -> self = self;
        funcCall -> name = name;
        funcCall -> params = params;


        return funcCall;


}

VariableNode * initVarNode(Node self, char * name){
    VariableNode * varNode = malloc(sizeof(VariableNode *));
    if(mallocError(varNode)) {
        return NULL;
    }


    // have to update variables value
    varNode -> self = self;
    varNode -> name = name;

    return varNode;

}


ConstantNode * initConstNode(Node self, VarType type, void * value){
    //initialize constant depending on type later? constant needs type?
    ConstantNode * constNode = malloc(sizeof(ConstantNode *));
    if(mallocError(constNode)) {
        return NULL;
    }

    constNode -> self = self;
    constNode -> type = type;
    constNode -> value = value;

    return constNode;


}

BinaryOperationNode * initBinaryOperationNode(Node self, Node * left, Node * right, char * op){
    BinaryOperationNode * binOpNode = malloc(sizeof(BinaryOperationNode *));
    if(mallocError(binOpNode)) {
        return NULL;
    }

    binOpNode -> self = self;
    binOpNode -> left = left;
    binOpNode -> right = right;
    binOpNode -> op = op;

    return binOpNode;

}


UnaryOperationNode * initUnaryOperationNode(Node self, Node * expression, char * op){
    UnaryOperationNode * unOpNode = malloc(sizeof(UnaryOperationNode *));
    if(mallocError(unOpNode)) {
        return NULL;
    }

    unOpNode -> self = self;
    unOpNode -> expression = expression;
    unOpNode -> op = op;

    return unOpNode;

}

BlockNode * initBlockNode(Node self, NodeList * statement){
    BlockNode * blockNode = malloc(sizeof(BlockNode *));
    if(mallocError(blockNode)) {
        return NULL;
    }

    blockNode -> self = self;
    blockNode -> statement = statement;

    return blockNode;

}


WhileNode * initWhileNode(Node self, NodeList * statements, Node * expression, Node * ret){
    WhileNode * whileNode = malloc(sizeof(WhileNode *));
    if(mallocError(whileNode)) {
        return NULL;
    }

    whileNode -> self = self;
    whileNode -> statements = statements;
    whileNode -> expression = expression;
    whileNode -> ret = ret;

    return whileNode;

}

IfNode * initIfNode(Node self, Node * ifExpression, Node  * ifBlock, Node * elseIfExpression, Node * elseBlock ){
    IfNode * ifNode = malloc(sizeof(IfNode *));
    if(mallocError(ifNode)) {
        return NULL;
    }

    ifNode -> self = self;
    ifNode -> ifExpression = ifExpression;
    ifNode -> ifBlock = ifBlock;
    ifNode -> elseIfExpression = elseIfExpression;
    ifNode -> elseIfBlock = elseBlock;


    return ifNode;

}


PrintNode * initPrintNode(Node self, Node * expression){
    PrintNode * printNode = malloc(sizeof(PrintNode *));
    if(mallocError(printNode)) {
        return NULL;
    }  


    printNode -> self = self;
    printNode -> expression = expression;


    return printNode;

}

MainNode  * initMainNode(Node self, NodeList * statements){
    MainNode * mainNode = malloc(sizeof(MainNode *));
    if(mallocError(mainNode)) {
        return NULL;
    }  

    mainNode -> self = self;
    mainNode -> statements = statements;

    return mainNode;
    
}


StatementNode * initStatement(Node self, Node * statement){

    StatementNode * statementNode = malloc(sizeof(StatementNode *));
    if(mallocError(statementNode)) return NULL;

    statementNode -> self = self;
    statementNode -> statement = statementNode;

    return statementNode;
}



