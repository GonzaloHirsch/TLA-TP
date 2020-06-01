#include "translation.h"

char * processStamentListNode(GenericNode * gn);
char * processWhileNode(GenericNode * gn);
char * process(GenericNode * gn);
char * processEntrypointNode(GenericNode * gn);
char * processBlock(GenericNode * gn);
char * processAssignment(GenericNode * gn);
char * processLeaf(GenericNode * gn);
char * processIf(GenericNode * gn);
char * processGeneralExpression(GenericNode * gn);


char * processInt(GenericNode * gn);
char * processInBlockStatements(GenericNode * gn);
char * processHyperStatement(GenericNode * gn);
char * processHyperStatements(GenericNode * gn);

char * processVariable(GenericNode * gn);
char * processDouble(GenericNode * gn);
char * processStr(GenericNode * gn);

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
        case NODE_ELSETRAIN:
            break;
        case NODE_STATEMENT:
            break;
        case NODE_VARDECLARATION:
            break;
        case NODE_VARDECLASSIGNMENT:
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
            // TODO implement
            value = processInt(gn);
        case NODE_STR:
            // TODO implement
            // value = processStr(gn);
        case NODE_DOUBLE:
            // TODO implement
            // value = processDouble(gn);
        case NODE_VARIABLE:
            // TODO implement
            // value = processVariable(gn);
            break;
        case NODE_LITERAL:
            value = processLeaf(gn);
            break;        
        case NODE_HYPERSTATEMENTS:
            // TODO implement
            value = processHyperStatements(gn);
            break;        
        case NODE_HYPERSTATEMENT:
            // TODO implement
            value = processHyperStatement(gn);
            break;
        case NODE_INBLOCKSTATEMENTS:
            // TODO implement
            value = processInBlockStatements(gn);
            break;
        case NODE_INBLOCKSTATEMENT:
            value = processStamentListNode(gn);
            break;
        case NODE_WHILE:
            value = processWhileNode(gn);
            break;

        case NODE_G_EXPRESSION:
            value = processGeneralExpression(gn);
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
        free(statements);
        return NULL;
    }

    // Calculating the length of the buffer
    size_t bufferSize = strlen("int main(){return 0;}") + strlen(statements) + 1;
    char * buffer = malloc(bufferSize);
    if (buffer == NULL){
        free(statements);
        return NULL;
    }

    // Printing the strings into the buffer
    sprintf(buffer, "int main(){%sreturn 0;}", statements);

    free(statements);

    return buffer;
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
        free(block);
        free(expression);
        return NULL;
    }

    // Printing the strings into the buffer
    sprintf(buffer, "while(%s){%s}", expression, block);

    free(block);
    free(expression);

    return buffer;
}

char * processStamentListNode(GenericNode * gn){
    char * buffer = malloc(1);
    if (buffer == NULL) {
        return NULL;
    }
    buffer[0] = '\0';

    if (gn == NULL){
        return buffer;
    }    

    NodeList * current = gn->children;
    GenericNode * currentNode;
    char * processedNode;
    while (current != NULL){
        // Getting the current Generic Node
        currentNode = current->current;
        if (currentNode == NULL){ 
            break; 
        }

        // Processing the current Generic Node
        processedNode = process(currentNode);
        if (processedNode == NULL){
            free(buffer);
            break;
        }

        // Saving new memory for the extended buffer
        buffer = realloc(buffer, strlen(processedNode) + strlen(buffer));
        if (buffer == NULL){
            free(processedNode);
            free(buffer);
            break;
        }

        // Concatenating the old buffer with the new processed info
        strcat(buffer, processedNode);

        current = current->next;
    }

    // Liberating the memory for the pointer to processed node
    free(processedNode);

    return buffer;
}



char * processNodeList(NodeList * current){
    char * buffer = malloc(1);
    if (buffer == NULL) {
        return NULL;
    }
    buffer[0] = '\0';

    GenericNode * currentNode;
    char * processedNode;
    while (current != NULL){
        // Getting the current Generic Node
        currentNode = current->current;
        if (currentNode == NULL){ 
            break; 
        }

        // Processing the current Generic Node
        processedNode = process(currentNode);
        if (processedNode == NULL){
            free(buffer);
            break;
        }

        // Saving new memory for the extended buffer
        buffer = realloc(buffer, strlen(processedNode) + strlen(buffer));
        if (buffer == NULL){
            free(processedNode);
            free(buffer);
            break;
        }

        // Concatenating the old buffer with the new processed info
        strcat(buffer, processedNode);
        free(processedNode);

        current = current->next;
    }

    // Liberating the memory for the pointer to processed node
    free(processedNode);

    return buffer;

}





char * processAssignment(GenericNode * gn){
    char * buffer = malloc(1);
    if (buffer == NULL) {
        return NULL;
    }
    buffer[0] = '\0';

    if (gn == NULL){
        return buffer;
    }

    NodeList * child = gn -> children;
    
    GenericNode * var = child -> current;

    char * varName = process(var);



    NodeList * valueNList = child ->next;

    char * valueNListProc = processNodeList(valueNList);



    buffer = realloc(buffer, strlen(varName) + strlen(" = ") + strlen(valueNListProc) + strlen(buffer));
    if (buffer == NULL | valueNListProc == NULL){
            // free(valueNList);
            free(varName);
            free(buffer);
            return NULL;
    }

    strcat(buffer, varName);
    strcat(buffer, " = ");
    strcat(buffer, valueNListProc);

    free(varName);
    free(valueNList);

    return buffer;
}



char * processLeaf(GenericNode * gn){
    char * buffer = malloc(1);
    if (buffer == NULL) {
        return NULL;
    }
    buffer[0] = '\0';

    if (gn == NULL){
        free(buffer);
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

char * processIf(GenericNode * gn){
    char * buffer = malloc(1);
    if (buffer == NULL) {
        return NULL;
    }
    buffer[0] = '\0';

    char * if_op = "if (";
    char * p_close = ")";
    
    GenericNode * ge = gn -> children -> current;
    
    char * geProc = process(ge);

    if(geProc == NULL){
        free(buffer);
        return NULL;
    }

    NodeList * block = gn -> children -> next;

    char * blockProc = processNodeList(block);
    if(blockProc ==  NULL){
        free(buffer);
        free(geProc);
        return NULL;
    }

    buffer = realloc(buffer, strlen(if_op) + strlen(geProc) + strlen(p_close) + strlen(blockProc) + strlen(buffer));

    if(buffer == NULL){
        free(buffer);
        free(geProc);
        free(blockProc);
        return NULL;
    }
    
    strcat(buffer, if_op);
    strcat(buffer, geProc);
    strcat(buffer, p_close);
    strcat(buffer, blockProc);

    free(geProc);
    free(blockProc);

    return buffer;

}



char * processBlock(GenericNode * gn){
    char * buffer = malloc(1);
    if (buffer == NULL) {
        return NULL;
    }
    buffer[0] = '\0';

    char * op_b;
    char * cl_b;

    strcpy(op_b, "{ \n");
    strcpy(cl_b, "\n }");

    if(gn == NULL){
        free(buffer);
        return NULL;
    }

    NodeList * child = gn -> children;
    char * processedBlock = processNodeList(child);
    if(processedBlock == NULL){
        free(buffer);
        return NULL;
    }


    buffer = realloc(buffer, strlen(op_b) + strlen(processedBlock) + strlen(cl_b) + strlen(buffer));
    
    if(buffer == NULL){
        free(processedBlock);
        free(buffer);
        return NULL;
    }


    
    strcat(buffer, op_b);
    strcat(buffer, processedBlock);
    strcat(buffer, cl_b);

    free(processedBlock);

    return buffer;

}

char * processInBlockStatements(GenericNode * gn) {
    return processNodeList(gn->children);
}

char * processHyperStatement(GenericNode * gn) {
    // Statements add the comma,
    // won't do checks here
    return process(gn->children->current);
}

char * processHyperStatements(GenericNode * gn) {
    return processNodeList(gn->children);
}




char * processGeneralExpression(GenericNode * gn){
    char * buffer = malloc(1);
    if (buffer == NULL) {
        return NULL;
    }
    buffer[0] = '\0';
    char * operatorValue = gn -> value;
    char * op;

    if(strcmp(operatorValue, "AND") == 0){
        op = " && ";
    }
    else if(strcmp(operatorValue, "OR") == 0)
    {   
        op = " | ";
    }
    else{
        op = "";
    }

    GenericNode * exp1 = gn -> children ->current;
    char * exp1Proc = process(exp1);


    if(strcmp(op, "") != 0){ //there is an operator to parse, then there is another expression
        GenericNode * exp2 = gn -> children -> next ->current;
        char * exp2Proc = process(exp2);
        if(exp2Proc == NULL){
            free(buffer);
            return NULL;
        }
        buffer = realloc(buffer, strlen(exp1Proc) + strlen(op) + strlen(exp2Proc) + strlen(buffer));
        if(buffer == NULL){
            free(exp1Proc);
            free(exp2Proc);
            return NULL;
        }
        strcat(buffer, exp1Proc);
        strcat(buffer, op);
        strcat(buffer, exp2Proc);

        free(exp1Proc);
        free(exp2Proc);

        return buffer;

    }

    // there is no other expression

    buffer = realloc(buffer, strlen(exp1Proc) + strlen(buffer));
    if(buffer == NULL){
        free(exp1Proc);
        return NULL;
    }

    strcat(buffer, exp1Proc);

    free(exp1Proc);

    return buffer;
}

//FUNCTIONS THAT NEED TO FINISH BEING IMPLEMENTED

char * processInt(GenericNode * gn) {
    printf("%s\n", gn->value);
    return gn->value;
}

// -------------------------- EXPOSED FUNCTIONS --------------------------

char * translate(GenericNode * gn){
    char * code = process(gn);
    return code;
}



