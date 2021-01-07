#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usefc.h"
#include "vertex.h"
#include "edge.h"
#include "matrix.h"
#include "graph.h"

int main(int argc, char *argv[]) {
	int v_argument_index, e_argument_index, mst_argument_index, mrn_argument_index;
	uint vertex_dlen = 0, edge_dlen = 0, edge_mst_dlen = 0;
	vertex *vertex_data;
	edge *edge_data, *edge_mst;
	/*matrix *a = NULL;*/
	graph *graph_temp = NULL;

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
	qsort(edge_data, edge_dlen, sizeof(edge), edge_compar_fn_by_id);
	printf("edges: %d\n",edge_dlen);
	/*edge_print(edge_data, edge_dlen);*/

/* finding minimal tree scelet */
	if(mst_argument_index>=0 || mrn_argument_index>=0){
		printf("mst testing\n");
		graph_temp = createGraph(vertex_dlen, edge_dlen, edge_data);	
		edge_mst = KruskalMST(graph_temp, vertex_data, &edge_mst_dlen);

		if(mst_argument_index>=0){
			printf("edge_mst_dlen:%d\n",edge_mst_dlen);
			edge_export_mst(edge_mst, edge_mst_dlen, argv[mst_argument_index+1]);
		}
		/*printf("edge_mst_dlen:%d\n",edge_mst_dlen);*/
		/*edge_print(edge_mst, edge_mst_dlen);*/
	} 
	return 0;
}