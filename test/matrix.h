#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "usefc.h"
#include "edge.h"
#include "vertex.h"

typedef struct {
	int rows, cols;
	real **items;
} matrix;

matrix *matrix_create(int rows, int cols);
void matrix_free(matrix **m);
void matrix_print(matrix *m);
void matrix_set(matrix *m, real value);
void matrix_set_edges(matrix *m, edge *edges, uint edge_dlen, vertex *vertexes, uint vertex_dlen);
matrix *matrix_add(matrix *a, matrix *b);

#endif