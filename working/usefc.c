#include <stdio.h>
#include <stdlib.h>
#include "usefc.h"
#include <string.h>

void printArrayString(int size, char **values){
    int i;
   
    if(size<1 || !values){
        printf("Wrong params given to printArrayString()!\n");
        return;
    }

    for(i=0; i < size; i++){
        printf("%d: '%s'\n",i , values[i]);
    }
    
}

/* najde prvek v poli stringu, pokud ne -> vrati -1 */
int inArrayString(int size, char **values, char *search){
    int found = -1, i;

    /* oseterni parametru */
    if(!size || size==0 || !values || !search ){
        printf("Wrong params given to inArrayString()!\n");
        return 0;
    }

    for(i=0;i<size;i++){
        if(strcmp(values[i], search)==0){
            found = i;
            break;
        }
    }
    return found;
}