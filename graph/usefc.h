#ifndef __USEFC_H__
#define __USEFC_H__

typedef unsigned int uint;
typedef double real;

/* vypise pole stringu */
void printArrayString(int size, char **values);

/* najde prvek v poli stringu, pokud ne -> vrati -1 */
int inArrayString(int size, char **values, char *search);

#endif