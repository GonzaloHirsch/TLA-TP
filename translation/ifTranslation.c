#include "ifTranslation.h"

char * processIf(GenericNode * gn){
    char * buffer;
    char * if_op = "if (";
    char * p_close = ")";
    
    //Gets and process general expression. ( .... )
    GenericNode * ge = gn -> children -> current;
    char * geProc = processGeneralExpression(ge);
    if(geProc == NULL){
        return NULL;
    }

    //Gets and process the block statement of the if.
    GenericNode * block = gn -> children -> next -> current;
    char * blockProc = processBlock(block);
    if(blockProc ==  NULL){
        //free(geProc);
        return NULL;
    }

    buffer = malloc(strlen(if_op) + strlen(geProc) + strlen(p_close) + strlen(blockProc) + 1);
    if(buffer == NULL){
        //free(buffer);
        //free(geProc);
        //free(blockProc);
        return NULL;
    }

    sprintf(buffer, "%s%s%s%s", if_op, geProc, p_close, blockProc);

    //free(geProc);
    //free(blockProc);

    return buffer;

}

char * processIfElse(GenericNode * gn){
    char * buffer;
    char * if_op = "if (";
    char * p_close = ")";
    
    //Gets and process general expression. ( .... )
    GenericNode * ge = gn -> children -> current;
    char * geProc = process(ge);
    if(geProc == NULL){
        return NULL;
    }

    //Gets and process the block statement of the if.
    GenericNode * block = gn -> children -> next -> current;
    char * blockProc = processBlock(block);
    if(blockProc ==  NULL){
        //free(geProc);
        return NULL;
    }

    // Process the else train
    GenericNode * elseTrain = gn -> children -> next -> next -> current; //Get the node of the else train.
    char * elseTrainProc = "ELSETRAIN\n";//processElseTrain(elseTrain);
    if(elseTrainProc == NULL){
        //free(elseTrainProc);
        return NULL;
    }

    buffer = malloc(strlen(if_op) + strlen(geProc) + strlen(p_close) + strlen(blockProc) + strlen(elseTrainProc) + 1);
    if(buffer == NULL){
        //free(buffer);
        //free(geProc);
        //free(blockProc);
        return NULL;
    }

    sprintf(buffer, "%s%s%s%s%s", if_op, geProc, p_close, blockProc, elseTrainProc);

    //free(geProc);
    //free(blockProc);

    return buffer;

}

char * processElseTrain(GenericNode * gn){
    char * buffer = malloc(1);
    if (buffer == NULL) {
        return NULL;
    }

    char * elseType = gn -> value; //Need to know what is the else type to parse correctly

    char * initial;




    if(strcmp(elseType, "ELSE") == 0){
        initial = " else { \n";
        GenericNode * block = gn -> children ->current;
        char * blockProc = process(block);
        if(blockProc == NULL){
            free(buffer);
            return NULL;
        }
        buffer = realloc(buffer, strlen(initial) + strlen(blockProc) + strlen(buffer));
        if(buffer == NULL){
            free(blockProc);
            return NULL;
        }
        strcat(buffer, initial);
        strcat(buffer, blockProc);
        free(blockProc);

        return buffer;

    }
    
    //is an elif

    initial = "else if( ";
    char * c_par = " ) ";

    GenericNode * ge = gn -> children -> current;
    char * geProc = process(ge);

    if(geProc == NULL){
        free(buffer);
        return NULL;
    }

    GenericNode * block = gn -> children -> next ->current;
    char * blockProc = process(block);
        if(blockProc == NULL){
            free(buffer);
            free(geProc);
            return NULL;
        }

    if(strcmp(elseType, "ELSE_IF_2") == 0){
        GenericNode * elseIf = gn -> children -> next ->next -> current;
        char * elseIfProc = process(elseIf);
        if(elseIfProc == NULL){
            free(buffer);
            free(geProc);
            free(blockProc);
            return NULL;
        }
        buffer = realloc(buffer, strlen(initial) + strlen(geProc) + strlen(c_par) + strlen(blockProc) + strlen(elseIfProc) + strlen(buffer));
        if(buffer == NULL){
            free(geProc);
            free(blockProc);
            free(elseIfProc);
            return NULL;
        }

        strcat(buffer,initial);
        strcat(buffer,geProc);
        strcat(buffer,c_par);
        strcat(buffer,blockProc);
        strcat(buffer,elseIfProc);
        free(geProc);
        free(blockProc);
        free(elseIfProc);

        return buffer;

    }
    else{ //elif type 1
        buffer = realloc(buffer, strlen(initial) + strlen(geProc) + strlen(c_par) + strlen(blockProc) + strlen(buffer));
        if(buffer == NULL){
            free(geProc);
            free(blockProc);
            return NULL;
        }

        strcat(buffer,initial);
        strcat(buffer,geProc);
        strcat(buffer,c_par);
        strcat(buffer,blockProc);
        free(geProc);
        free(blockProc);

        return buffer;

    }
    return buffer;
}