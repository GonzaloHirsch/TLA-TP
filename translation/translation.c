#include "translation.h"



// -------------------------- PRIVATE FUNCTIONS --------------------------

char * process(GenericNode * gn){
    char * value = NULL;
    if (gn == NULL){
        return value;
    }
    switch (gn->info.type){
        case NODE_LIST:
            break;
        case NODE_FUNCTIONS:
            break;
        case NODE_ENTRYPOINT:  
            value = processEntrypointNode(gn);
            break;
        case NODE_IFSENTENCE:
            value = processIf(gn);
            break;
        case NODE_IFSENTENCE_ELSE:
            value = processIfElse(gn);
            break;
        case NODE_ELSETRAIN:
            value = processElseTrain(gn);
            break;
        case NODE_STATEMENT:
            value = processStatement(gn);
            break;
        case NODE_VARDECLARATION:
            value = processVarDeclaration(gn);
            break;
        case NODE_VARDECLASSIGNMENT:
            value = processVarDeclassignment(gn);
            break;
        case NODE_FOREACH:
            break;
        case NODE_FOREACHBODY:
            break;
        case NODE_BLOCK:
            value = processBlock(gn);
            break;
        case NODE_FUNBLOCK:
            break;
        case NODE_ASSIGNMENT:
            value = processAssignment(gn);
            break;
        case NODE_INT:
            value = processInt(gn);
            break;
        case NODE_STR:
            value = processStr(gn);
            break;
        case NODE_DOUBLE:
            value = processDouble(gn);
            break;
        case NODE_VARIABLE:
            value = processVariable(gn);
            break;
        case NODE_LITERAL:
            value = processLeaf(gn);
            break;        
        case NODE_HYPERSTATEMENTS:
            value = processHyperStatements(gn);
            break;        
        case NODE_HYPERSTATEMENT:
            value = processHyperStatement(gn);
            break;
        case NODE_INBLOCKSTATEMENTS:
            value = processInBlockStatements(gn);
            break;
        case NODE_INBLOCKSTATEMENT:
            value = processInBlockStatement(gn);
            break;
        case NODE_WHILE:
            value = processWhileNode(gn);
            break;
        case NODE_G_EXPRESSION:
            value = processGeneralExpression(gn);
            break;

        case NODE_EXPRESSION:
            value = processExpression(gn);
            break;

        case NODE_G_OPERATION:
            value = "general_operation";
            break;
        case NODE_OPERATION:
            value = "operation";
            break;


        default:
            break;
    }

    return value;
}



char * processEntrypointNode(GenericNode * gn){
    if (gn == NULL){
        return NULL;
    }    

    // Getting the nodelist with the statements
    NodeList * statementsListNode = gn->children;
    if (statementsListNode == NULL){
        return NULL;
    }

    // Getting the node with the statements and processing it
    GenericNode * statementsNode = statementsListNode->current;
    char * statements = process(statementsNode);
    if (statements == NULL){
        //free(statements);
        return NULL;
    }

    // Calculating the length of the buffer
    size_t bufferSize = strlen("int main(){return 0;}") + strlen(statements) + 1;
    char * buffer = malloc(bufferSize);
    if (buffer == NULL){
        //free(statements);
        return NULL;
    }

    // Printing the strings into the buffer
    sprintf(buffer, "int main(){%sreturn 0;}", statements);

    //free(statements);

    return buffer;
}

char * processHyperStatement(GenericNode * gn) {
    // Statements add the comma,
    // won't do checks here
    return process(gn->children->current);
}

char * processHyperStatements(GenericNode * gn) {
    return processNodeList(gn->children);
}

char * processNodeList(NodeList * listCurrent){
    if (listCurrent == NULL) return NULL;
    
    char * buffer = malloc(1);
    if (buffer == NULL) return NULL;

    buffer[0] = '\0';  

    GenericNode * currentNode;
    char * processedNode;

    //Iteration through the statement list.
    while(listCurrent != NULL){
        // Getting the current Generic Node
        currentNode = listCurrent->current;
        if (currentNode == NULL){ 
            break; 
        }

        // Processing the current Generic Node
        processedNode = process(currentNode);
        if (processedNode == NULL){
            //free(buffer);
            break;
        }
        
        // Saving new memory for the extended buffer                             
        buffer = realloc(buffer, 1 + strlen(buffer) +  strlen(processedNode));
        if (buffer == NULL){
            //free(processedNode);
            //free(buffer);
            break;
        }

        // Concatenating the old buffer with the new processed node.
        strcat(buffer, processedNode);

        listCurrent = listCurrent->next;
    }

    // Free the memory for the pointer to processed node
    //free(processedNode);

    return buffer;
}


char * processAssignment(GenericNode * gn){
    if (gn == NULL) return NULL;

    char * buffer;
    GenericNode * var = gn->children->current;
    GenericNode * rightValue = gn->children->next->current;

    //Process the variable
    char * varName = process(var);
    //Process the right value of the expression(literal, generalExp or genOp)
    char * rightValueProc = process(rightValue);

    buffer = malloc(1 + strlen(varName) + strlen(" = ") + strlen(rightValueProc));
    if (buffer == NULL){
        //free(valueNListProc);
        //free(varName);
        //free(buffer);
        return NULL;
    }

    sprintf(buffer, "%s = %s", varName, rightValueProc);

    //free(varName);
    //free(varNListProc)

    return buffer;
}



char * processLeaf(GenericNode * gn){
    char * buffer = malloc(1);
    if (buffer == NULL) {
        return NULL;
    }
    buffer[0] = '\0';

    if (gn == NULL){
        //free(buffer);
        return NULL;
    }  


    char * value = gn -> value;

    buffer = realloc(buffer, strlen(value) + strlen(buffer));
    if (buffer == NULL){
        return NULL;
    }


    strcat(buffer, value);

    

    return buffer;

}

char * processBlock(GenericNode * gn){
    if(gn == NULL) return NULL;
    
    char * buffer;
    char * op_b = "{\n";
    char * cl_b = "\n}";

    //Get the child node which has a inblockstament list.
    GenericNode * child = gn->children->current;
    char * processedBlock = processInBlockStatements(child);
    if(processedBlock == NULL){
        //free(buffer);
        return NULL;
    }

    buffer = malloc( 1 + strlen(op_b) + strlen(processedBlock) + strlen(cl_b));
    if(buffer == NULL){
        //free(processedBlock);
        //free(buffer);
        return NULL;
    }

    sprintf(buffer, "%s%s%s", op_b, processedBlock, cl_b);

    //free(processedBlock);

    return buffer;
}

char * processInBlockStatements(GenericNode * gn) {
    //Pass the children of the node, its a NodeList.
    return processNodeList(gn->children);
}

char * processInBlockStatement(GenericNode * gn){
    processStatement(gn);
}

char * processWhileNode(GenericNode * gn){
    if (gn == NULL){
        return NULL;
    }    

    // Getting the nodelist with the expression
    NodeList * expressionListNode = gn->children;
    if (expressionListNode == NULL){
        return NULL;
    }

    // Getting the node with the expression and processing it
    GenericNode * expressionNode = expressionListNode->current;
    char * expression = process(expressionNode);
    if (expression == NULL){
        return NULL;
    }

    // Getting the nodelist with the block
    NodeList * blockListNode = expressionListNode->next;
    if (blockListNode == NULL){
        return NULL;
    }

    // Getting the node with the block and processing it 
    GenericNode * blockNode = blockListNode->current;
    char * block = process(blockNode);
    if (block == NULL){
        return NULL;
    }

    // Calculating the length of the buffer
    size_t bufferSize = strlen("while(){}") + strlen(block) + strlen(expression) + 1;
    char * buffer = malloc(bufferSize);
    if (buffer == NULL){
        ////free(block);
        ////free(expression);
        return NULL;
    }

    // Printing the strings into the buffer
    sprintf(buffer, "while(%s){%s}", expression, block);

    ////free(block);
    ////free(expression);

    return buffer;
}

// -------------------------- EXPOSED FUNCTIONS --------------------------

char * translate(GenericNode * gn){
    char * code = process(gn);
    return code;
}



