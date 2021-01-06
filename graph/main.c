#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usefc.h"
#include "vertex.h"
#include "edge.h"
#include "matrix.h"

#define LINE_LEN 256

int main(int argc, char *argv[]) {
	int v_argument_index, e_argument_index, mst_argument_index, mrn_argument_index;
	uint vertex_dlen = 0, edge_dlen = 0;
	vertex *vertex_data;
	edge *edge_data;
	matrix *a = NULL;

/* argument validation */
	if(argc < 4){
		printf("Error: Invalid argument count!\n");
		return EXIT_FAILURE;
	} 
	
	v_argument_index = inArrayString(argc, argv, "-v");
	e_argument_index = inArrayString(argc, argv, "-e");
	mst_argument_index = inArrayString(argc, argv, "-mst");
	mrn_argument_index = inArrayString(argc, argv, "-mrn");
	 
	if(v_argument_index<0 || e_argument_index<0){
		printf("Error: Invalid argument count!\n");
		return EXIT_FAILURE;
	} 

/* vertex load */
	vertex_data = vertex_load(argv[v_argument_index+1], &vertex_dlen);
	if(!vertex_dlen){
		return 1;
	}
	qsort(vertex_data, vertex_dlen, sizeof(vertex), vertex_compar_fn);
	printf("vertexes: %d\n",vertex_dlen);
	/*vertex_print(vertex_data, vertex_dlen);*/

/* edge load */
	edge_data = edge_load(argv[e_argument_index+1], &edge_dlen);
	if(!edge_dlen){
		return 2;
	}
	qsort(edge_data, edge_dlen, sizeof(edge), edge_compar_fn);
	printf("edges: %d\n",edge_dlen);
	/*edge_print(edge_data, edge_dlen);*/

/* minimal tree scalet */
	if(mst_argument_index>=0)
		printf("ready for argument mst\n");

/* minimal tree scalet with all stuff */		
	if(mrn_argument_index>=0)
		printf("ready for argument mrn\n");

/* finding minimal tree scelet */
	if(mst_argument_index>=0 || mrn_argument_index>=0){
		printf("matrix testing\n");

/*		a = matrix_create(5, 5);
		matrix_set(a, 1.0);
		a->items[2][3] = 5.0;

		matrix_print(a);

		matrix_free(&a);*/

		a = matrix_create(vertex_dlen, vertex_dlen);
		matrix_set_edges(a, edge_data, edge_dlen, vertex_data, vertex_dlen);
		/*matrix_print(a);*/
		printf("clen on 1x2: %f\n",a->items[vertex_get_key_by_id(vertex_data, vertex_dlen, 1)][vertex_get_key_by_id(vertex_data, vertex_dlen, 2)]);
		printf("clen on 1x2: %f\n",a->items[0][1]);
		matrix_free(&a);
	}

	return 0;
}