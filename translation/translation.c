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
            value = processStamentListNode(gn);
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
            ////free(buffer);
            break;
        }

        // Saving new memory for the extended buffer
        buffer = realloc(buffer, strlen(processedNode) + strlen(buffer));
        if (buffer == NULL){
            //free(processedNode);
            //free(buffer);
            break;
        }

        // Concatenating the old buffer with the new processed info
        strcat(buffer, processedNode);

        current = current->next;
    }

    // Liberating the memory for the pointer to processed node
    //free(processedNode);

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
            //free(buffer);
            break;
        }

        // Saving new memory for the extended buffer
        buffer = realloc(buffer, strlen(processedNode) + strlen(buffer));
        if (buffer == NULL){
            //free(processedNode);
            //free(buffer);
            break;
        }

        // Concatenating the old buffer with the new processed info
        strcat(buffer, processedNode);
        //free(processedNode);

        current = current->next;
    }

    // Liberating the memory for the pointer to processed node
    //free(processedNode);

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
            // //free(valueNList);
            //free(varName);
            //free(buffer);
            return NULL;
    }

    strcat(buffer, varName);
    strcat(buffer, " = ");
    strcat(buffer, valueNListProc);

    //free(varName);

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

    NodeList * child = gn -> children;
    char * processedBlock = "INBLOCKSTATEMENTS";//processNodeList(child);
    if(processedBlock == NULL){
        //free(buffer);
        return NULL;
    }

    buffer = malloc( 1 + strlen(op_b) + strlen(processedBlock) + strlen(cl_b) + strlen(buffer));
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
            //free(buffer);
            return NULL;
        }
        buffer = realloc(buffer, strlen(exp1Proc) + strlen(op) + strlen(exp2Proc) + strlen(buffer));
        if(buffer == NULL){
            //free(exp1Proc);
            //free(exp2Proc);
            return NULL;
        }
        strcat(buffer, exp1Proc);
        strcat(buffer, op);
        strcat(buffer, exp2Proc);

        //free(exp1Proc);
        //free(exp2Proc);

        return buffer;

    }

    // there is no other expression

    buffer = realloc(buffer, strlen(exp1Proc) + strlen(buffer));
    if(buffer == NULL){
        //free(exp1Proc);
        return NULL;
    }

    strcat(buffer, exp1Proc);

    //free(exp1Proc);

    return buffer;
}


char * processExpression(GenericNode * gn){
    char * buffer = malloc(1);
    if (buffer == NULL) {
        return NULL;
    }
    buffer[0] = '\0';

    GenericNode * exp1 = gn ->children -> current;
    char * exp1Proc = process(exp1);
    if(exp1Proc == NULL){
        free(buffer);
        return NULL;
    }

    char * opString = gn -> value;
    char * op;
    if(strcmp(opString, "EQ") == 0){
        op = " == ";
    }
    else if(strcmp(opString, "GT") == 0){
        op = " > ";
    }
    else if(strcmp(opString, "GE") == 0){
        op = " >= ";
    }
    else if(strcmp(opString, "LT") == 0){
        op = " < ";
    }
    else if(strcmp(opString, "LE") == 0){
        op = " >= ";
    }
    else if(strcmp(opString, "NE") == 0){
        op = " != ";
    }
    else if(strcmp(opString, "NOT") == 0){
        op = " !";

        buffer = realloc(buffer, strlen(op) + strlen(exp1Proc) + strlen(buffer));
        if(buffer == NULL){
            free(exp1Proc);
            return NULL;
        }

        strcat(buffer, op);
        strcat(buffer, exp1Proc);

        free(exp1Proc);

        return buffer;

    }
    
    // is not an unary expression

    GenericNode * exp2 = gn -> children -> next -> current;
    char * exp2Proc = process(exp2);
    if(exp2Proc == NULL){
        free(buffer);
        free(exp1Proc);
        return NULL;
    }




    buffer = realloc(buffer, strlen(op) + strlen(exp1Proc) + strlen(exp2Proc) + strlen(buffer));
    if(buffer == NULL){
        free(exp1Proc);
        free(exp2Proc);
        return NULL;
    }

    //example:  var1 >= var2
    strcat(buffer, exp1Proc);
    strcat(buffer, op);
    strcat(buffer, exp2Proc);
    free(exp1Proc);
    free(exp2Proc);


    return buffer;

}






// -------------------------- EXPOSED FUNCTIONS --------------------------

char * translate(GenericNode * gn){
    char * code = process(gn);
    return code;
}



