#ifndef __MATRIX_H__
#define __MATRIX_H__

typedef double real;

typedef struct {
	int rows, cols;
	real **items;
} matrix;

matrix *matrix_create(int rows, int cols);
void matrix_free(matrix **m);

void matrix_print(matrix *m);
void matrix_set(matrix *m, real value);

matrix *matrix_add(matrix *a, matrix *b);

#endif