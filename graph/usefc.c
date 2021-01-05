#include <stdio.h>
#include <stdlib.h>
#include "usefc.h"

void printArrayString(int size, char **values){
    int i;
   
    if(size<1){
        printf("Invalid argument set for function printArrayString()!");
        return;
    }

    for(i=0; i < size; i++){
        printf("%d: '%s'\n",i, values[i]);
    }
    
}

int inArrayString(int size, char **values, char *search){
    if(!size || size ==0 || !values || !search ){
        return 0;
    }

    int found = -1, i;
    for(i=0;i<size;i++){
        if(strcmp(values[i], search)==0){
            found = i;
            break;
        }
    }

    return found;
}