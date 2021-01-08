#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usefc.h"
#include "vertex.h"
#include "edge.h"
#include "graph.h"

int main(int argc, char *argv[]) {
	int v_argument_index, e_argument_index, mst_argument_index, mrn_argument_index;
	uint vertex_dlen = 0, edge_dlen = 0, edge_mst_dlen = 0, i;
	vertex *vertex_data;
	edge *edge_data, *edge_mst;
	graph *graph_temp = NULL;

/* validace argumentu */
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

/* nacitani vrcholu */
	vertex_data = vertex_load(argv[v_argument_index+1], &vertex_dlen);
	if(!vertex_dlen){
		return 1;
	}
	qsort(vertex_data, vertex_dlen, sizeof(vertex), vertex_compar_fn);

/* nacitani hran */
	edge_data = edge_load(argv[e_argument_index+1], &edge_dlen);
	if(!edge_dlen){
		free(vertex_data);
		return 2;
	}
	qsort(edge_data, edge_dlen, sizeof(edge), edge_compar_fn_by_id);

/* hledani minimalni kostry grafu */
	if(mst_argument_index>=0 || mrn_argument_index>=0){
		graph_temp = createGraph(vertex_dlen, edge_dlen, edge_data);	
		if(!graph_temp){	
			for(i=0;i<edge_dlen;i++){
				free(edge_data[i].wkt_pointer);
			}		
			free(edge_data);
			free(vertex_data);
			return EXIT_FAILURE;
		}

		edge_mst = KruskalMST(graph_temp, vertex_data, &edge_mst_dlen);
		if(!graph_temp){	
			free(graph_temp);	
			for(i=0;i<edge_dlen;i++){
				free(edge_data[i].wkt_pointer);
			}	
			free(edge_data);
			free(vertex_data);
			return EXIT_FAILURE;
		}
		if(mst_argument_index>=0){
			edge_export_mst(edge_mst, edge_mst_dlen, argv[mst_argument_index+1]);
		}

		if(mrn_argument_index>=0){
			edge_export_mrn(edge_mst, edge_mst_dlen, argv[mrn_argument_index+1]);
		}
	}else{		
		for(i=0;i<edge_dlen;i++){
			free(edge_data[i].wkt_pointer);
		}
		free(edge_data);
		free(vertex_data);
		return EXIT_SUCCESS;
	} 

printf("edge_dlen:%d",edge_dlen);
edge_print(edge_data, edge_dlen);
/* vraceni pameti */
		
	free(edge_mst);
	free(graph_temp);
	for(i=0;i<edge_dlen;i++){
		free(edge_data[i].wkt_pointer);
	}
	free(edge_data);
	free(vertex_data);

	return 0;
}