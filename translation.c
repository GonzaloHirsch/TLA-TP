#include "translation.h"

char * processStamentListNode(GenericNode * gn);
char * processWhileNode(GenericNode * gn);
char * process(GenericNode * gn);
char * processEntrypointNode(GenericNode * gn);

// -------------------------- PRIVATE FUNCTIONS --------------------------

char * process(GenericNode * gn){
    char * value = NULL;
    if (gn == NULL){
        return value;
    }
    char * code = malloc;
    switch (gn->info.type){
        case NODE_LIST:
            break;
        case NODE_FUNCTIONS:
            break;
        case NODE_ENTRYPOINT:  
            value = processEntrypointNode(gn);
            break;
        case NODE_IFSENTENCE:
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
            break;
        case NODE_FUNBLOCK:
            break;
        case NODE_ASSIGNMENT:
            break;
        case NODE_LITERAL:
            break;        
        case NODE_HYPERSTATEMENTS:
        case NODE_HYPERSTATEMENT:
        case NODE_INBLOCKSTATEMENTS:
        case NODE_INBLOCKSTATEMENT:
            value = processStamentListNode(gn);
            break;
        case NODE_WHILE:
            value = processWhileNode(gn);
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
        free(statementsListNode);
        free(statementsNode);
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
        free(expressionListNode);
        free(expressionNode);
        free(blockListNode);
        free(blockNode);
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

// -------------------------- EXPOSED FUNCTIONS --------------------------

char * translate(GenericNode * gn){
    char * code = process(gn);
    return code;
}