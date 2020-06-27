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
        free(geProc);
        return NULL;
    }

    buffer = malloc(strlen(if_op) + strlen(geProc) + strlen(p_close) + strlen(blockProc) + 1);
    if(buffer == NULL){
        free(geProc);
        free(blockProc);
        return NULL;
    }

    sprintf(buffer, "%s%s%s%s", if_op, geProc, p_close, blockProc);

    free(geProc);
    free(blockProc);

    return buffer;

}

char * processIfElse(GenericNode * gn){
    if(gn == NULL) return NULL;

    char * buffer;
    char * if_op = "if (";
    char * p_close = ")";

    
    //Gets and process general expression. ( .... )
    GenericNode * ge = gn -> children -> current;
    char * geProc = translate(ge);
    if(geProc == NULL){
        return NULL;
    }

    //Gets and process the block statement of the if.
    GenericNode * block = gn -> children -> next -> current;
    char * blockProc = processBlock(block);
    if(blockProc ==  NULL){
        free(geProc);
        return NULL;
    }

    // Process the else train
    GenericNode * elseTrain = gn -> children -> next -> next -> current; //Get the node of the else train.
    char * elseTrainProc = processElseTrain(elseTrain);
    if(elseTrainProc == NULL){
        free(geProc);
        free(blockProc);
        return NULL;
    }

    buffer = malloc(1+ strlen(if_op) + strlen(geProc) + strlen(p_close) + strlen(blockProc) + strlen(elseTrainProc) );
    if(buffer == NULL){
        free(elseTrainProc);
        free(geProc);
        free(blockProc);
        return NULL;
    }

    sprintf(buffer, "%s%s%s%s%s", if_op, geProc, p_close, blockProc, elseTrainProc);

    free(elseTrainProc);
    free(geProc);
    free(blockProc);

    return buffer;

}

char * processElseTrain(GenericNode * gn){
    char * buffer;

    // Need to know what is the else type to parse correctly
    char * elseType = gn -> value;
    char * initial;

    // Its a simple "ELSE"
    if(strcmp(elseType, "ELSE") == 0){
        initial = " else";
        GenericNode * block = gn -> children ->current;

        char * blockProc = translate(block);
        if(blockProc == NULL){
            return NULL;
        }

        buffer = malloc(1 +  strlen(initial) + strlen(blockProc));
        if(buffer == NULL){
            free(blockProc);
            return NULL;
        }

        sprintf(buffer, "%s%s", initial, blockProc);
        free(blockProc);

        return buffer;

    }
    
    // Its an "ELIF"

    initial = "else if( ";
    char * c_par = " ) ";

    GenericNode * ge = gn->children->current;

    //Process the general expression that both types of else if have.
    char * geProc = translate(ge);
    if(geProc == NULL){
        return NULL;
    }

    //Process the block that both types of else if have.
    GenericNode * block = gn -> children -> next ->current;
    char * blockProc = translate(block);
        if(blockProc == NULL){
            free(geProc);
            return NULL;
        }


    //Elif type 1 --> With no else train.
    if(strcmp(elseType, "ELSE_IF_1") == 0){ 

        buffer = malloc(1 + strlen(initial) + strlen(geProc) + strlen(c_par) + strlen(blockProc));
        if(buffer == NULL){
            free(geProc);
            free(blockProc);
            return NULL;
        }

        sprintf(buffer,"%s%s%s%s", initial, geProc, c_par, blockProc);
        free(geProc);
        free(blockProc);

        return buffer;

    }

    //Else if type 2 --> Same as before but with else train
    else if(strcmp(elseType, "ELSE_IF_2") == 0){

        GenericNode * elseIf = gn -> children -> next -> next -> current;

        char * elseIfProc = translate(elseIf);
        if(elseIfProc == NULL){
            free(geProc);
            free(blockProc);
            return NULL;
        }

        buffer = malloc(1 + strlen(initial) + strlen(geProc) + strlen(c_par) + strlen(blockProc) + strlen(elseIfProc));
        if(buffer == NULL){
            free(geProc);
            free(blockProc);
            free(elseIfProc);
            return NULL;
        }

        sprintf(buffer, "%s%s%s%s%s", initial, geProc, c_par, blockProc, elseIfProc);
        free(geProc);
        free(blockProc);
        free(elseIfProc);

        return buffer;

    }

    return NULL;
}