#include <stdio.h>
#include <stdlib.h>
#include "usefc.h"
#include <string.h>

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
    int found = -1, i;

    if(!size || size ==0 || !values || !search ){
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

/**
 * needs to free pointer after usage
 */
char *substring(char *string, int position, int length) 
{
   char *pointer;
   int c;

   pointer = malloc(length+1);

   if (pointer == NULL)
   {
      printf("Unable to allocate memory.\n");
      exit(1);
   }

   for (c = 0 ; c < length ; c++)
   {
      *(pointer+c) = *(string+position-1);      
      string++;   
   }

   *(pointer+c) = '\0';

   return pointer;
}