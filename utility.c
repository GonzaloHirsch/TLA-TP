#include "utility.h"

char * c_string(char *a1, char * a2, char * a3, char *a4, char *a5){
    char * ans = malloc(LENGTH * sizeof(char));

    strcpy(ans, a1);
    strcat(ans, " ");
    strcat(ans, a2);
    strcat(ans, " ");
    strcat(ans, a3);
    strcat(ans, " ");
    strcat(ans, a4);
    strcat(ans, " ");
    strcat(ans, a5);
    strcat(ans, " ");

    return ans;


}



