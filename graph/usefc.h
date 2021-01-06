#ifndef __USEFC_H__
#define __USEFC_H__

typedef unsigned int uint;
typedef double real;

void printArrayString(int size, char **values);
int inArrayString(int size, char **values, char *search);
char *substring(char *string, int position, int length);

#endif