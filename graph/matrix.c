#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "edge.h"
#include "usefc.h"
#include "vertex.h"

matrix *matrix_create(int rows, int cols){
	matrix *temp = NULL;
	int i;

	if(!rows || !cols) return NULL;

	temp = (matrix *) malloc(sizeof(matrix));
	if(!temp) return NULL;

	temp->rows = rows;
	temp->cols = cols;
	temp->items = (real **) malloc(rows * sizeof(real *));  /*rows krát velikost ukazatelu na real*/
	if(!temp->items){
		free(temp);
		return NULL;
	}

	for(i = 0; i < rows; i++){
		temp->items[i] = malloc(cols * sizeof(real));
		if(!temp->items[i]){
			for(i--; i >= 0; i--){
				free(temp->items[i]);
			}

			free(temp->items);
			free(temp);

			return NULL;
		}
	}
	matrix_set(temp, 0.0);
	return temp;
}


void matrix_print(matrix *m){
	int i,j;

	if(!m){
		printf("|x|\n");
		return;
	} 

	for(i=0;i< m->rows;i++){
		printf("| ");
		for(j=0;j< m->cols;j++){
			/*if( m->items[i][j] > 0)*/
			printf("%.2f ", m->items[i][j]);
		}
		printf("|\n");
	}
}

void matrix_free(matrix **m){
	int i;

	if(!*m) return;

	for(i = 0; i < (*m)->rows; i++ ){
		free((*m)->items[i]);
	}
	free((*m)->items);
	free(*m);
	*m = NULL;
}

void matrix_set(matrix *m, real value){
	int i, j;

	if(!m) return;

	for(i = 0; i < m->rows; i++){
		for(j = 0; j < m->cols; j++){
			m->items[i][j] = value;
		}
	}
}

void matrix_set_edges(matrix *m, edge *edges, uint edge_dlen, vertex *vertexes, uint vertex_dlen){
	uint i;
	int source, target;
	for(i=0; i<edge_dlen;i++){
		source = vertex_get_key_by_id(vertexes, vertex_dlen, edges[i].source);
		target = vertex_get_key_by_id(vertexes, vertex_dlen, edges[i].target);
		/*printf("clen %dx%d | %dx%d: %f\n",source, target, edges[i].source, edges[i].target, edges[i].clength);*/
		if(source>=0 && target>=0){
			m->items[source][target] = edges[i].clength;
			m->items[target][source] = edges[i].clength;
		}else{
			break;
		}
	}
}

matrix *matrix_add(matrix *a, matrix *b){
	matrix *r;
	int j,i;

	if(!a || !b || a->rows != b->rows || a->cols != b->cols)	 
		return NULL;

	r = matrix_create(a->rows, a->cols);
	if(!r) return NULL;

	for(i=0;i< r->rows;i++){
		for(j=0;j< r->cols;j++){
			r->items[i][j] = a->items[i][j] + b->items[i][j];
		}
	}

	return r;
}