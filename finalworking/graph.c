#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edge.h"
#include "graph.h"
#include "usefc.h"
#include "vertex.h"
 
 /*
vytvori graf a nacte predane hrany
*/
graph* createGraph(uint vertex_dlen, uint edge_dlen, edge *edges){
    graph* temp;

    if(vertex_dlen == 0 || edge_dlen == 0 || !edges){
        printf("Wrong params given to createGraph()!\n");
        return NULL;
    }

    temp = (graph*)malloc(sizeof(graph));
    if(!temp){
        printf("Memory allocation failed in createGraph()!\n");
        return NULL;
    }

    temp->vertex_dlen = vertex_dlen;
    temp->edge_dlen = edge_dlen;
 
    temp->edges = edges;
 
    return temp;
}
 
 /*
najde zakladni prvek indexu i
*/
uint find(subset subsets[], uint i)
{
    if(!subsets){
        printf("Wrong params given to find()!\n");
        return 0;
    }

    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}
 
 /*
spojeni dovu subsetu x,y
*/
void Union(subset subsets[], int x, int y)
{
    uint xroot;
    uint yroot;

    if(!subsets){
        printf("Wrong params given to Union()!\n");
        return;
    }

    xroot = find(subsets, x);
    yroot = find(subsets, y);
 
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
 
 /* 
funkce algoritmus hledajici mst 
*/
edge* KruskalMST(graph* graph_temp, vertex *vertex_data, uint *edge_mst_len)
{   
    uint vertex_dlen, e = 0, i = 0, j, minimumCost = 0;
    edge *result;
    subset *subsets;

    /* overeni parametru */
    if(!graph_temp || !vertex_data || !edge_mst_len){
        printf("Wrong params given to KruskalMST()!\n");
        return NULL;
    }

    vertex_dlen = graph_temp->vertex_dlen;
    result = (edge *)malloc(sizeof(edge)*vertex_dlen);      /* bylo by vhodne pridat dynamicke alokovani, aby se setrilo pameti */
    if(!result){
        printf("Memory allocation failed in KruskalMST()!\n");
        return NULL;
    }

    /* serazeni hran podle clength*/    
    qsort(graph_temp->edges, graph_temp->edge_dlen, sizeof(edge),edge_compar_fn_by_clen);   

    subsets = (subset*)malloc(vertex_dlen * sizeof(subset));
    if(!subsets){
        printf("Memory allocation failed in KruskalMST()!\n");
        free(result);
        return NULL;
    }

    /* inicializace subsets - parent= id, rank = 0 */
    for (j = 0; j < vertex_dlen; ++j) {
        subsets[j].parent = j;
        subsets[j].rank = 0;
    }
 
    while (e < (vertex_dlen - 1) && i < graph_temp->edge_dlen) {
        edge next_edge = graph_temp->edges[i++];
        uint x = 0;
        uint y = 0;

        /* overeni zda dany vrchol existuje */
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
    
    /* vypocet minimalni ceny - nevyuzite */
    for (i = 0; i < e; ++i){
        minimumCost += result[i].clength;
    }
    
    *edge_mst_len = e;
    free(subsets);
    return result;
}