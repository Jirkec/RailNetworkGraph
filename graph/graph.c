#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edge.h"
#include "graph.h"
#include "usefc.h"
#include "vertex.h"
 
graph* createGraph(uint vertex_dlen, uint edge_dlen, edge *edges){
    graph* temp = (graph*)malloc(sizeof(graph));
    temp->vertex_dlen = vertex_dlen;
    temp->edge_dlen = edge_dlen;
 
    temp->edges = edges;
 
    return temp;
}
 
uint find(subset subsets[], uint i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}
 
void Union(subset subsets[], int x, int y)
{
    uint xroot = find(subsets, x);
    uint yroot = find(subsets, y);
 
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
 
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
 
edge* KruskalMST(graph* graph_temp, vertex *vertex_data, uint *edge_mst_len)
{   
    uint vertex_dlen = graph_temp->vertex_dlen, e = 0, i = 0, j, minimumCost = 0;
    edge *result = (edge *)malloc(sizeof(edge)*vertex_dlen);         /* bylo by vhodne pridat dynamicke alokovani */
    subset *subsets;

    qsort(graph_temp->edges, graph_temp->edge_dlen, sizeof(edge),edge_compar_fn_by_clen);   /* serazeni hran podle clength*/

    subsets = (subset*)malloc(vertex_dlen * sizeof(subset));

    /* inicializace subsets - parent= id, rank = 0 */
    for (j = 0; j < vertex_dlen; ++j) {
        subsets[j].parent = j;
        subsets[j].rank = 0;
    }
 
    while (e < (vertex_dlen - 1) && i < graph_temp->edge_dlen) {
        edge next_edge = graph_temp->edges[i++];
        uint x = 0;
        uint y = 0;
        int vertex_source = (int)vertex_get_key_by_id(vertex_data, vertex_dlen, next_edge.source);
        int vertex_target = (int)vertex_get_key_by_id(vertex_data, vertex_dlen, next_edge.target);
        
        if (vertex_source>=0 && vertex_target>=0){
            x = find(subsets, vertex_source);
            y = find(subsets, vertex_target);
        }  
 
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }
    
    for (i = 0; i < e; ++i){
        minimumCost += result[i].clength;
    }
    
    *edge_mst_len = e;
    return result;
}