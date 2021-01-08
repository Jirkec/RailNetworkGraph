#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "usefc.h"
#include "edge.h"
#include "vertex.h"

/* struktura ohodnoceneho grafu */
typedef struct thegraph {
    uint vertex_dlen, edge_dlen;
    edge *edges;
} graph;

/* pomocna struktura k hledani spojenych hran/vrcholu */
typedef struct thesubset {
    uint parent;
    int rank;
} subset;

/*
vytvori graf a nacte predane hrany
*/
graph* createGraph(uint vertex_dlen, uint edge_dlen, edge *edges);

/*
najde zakladni prvek indexu i
*/
uint find(subset subsets[], uint i);

/*
spojeni dovu subsetu x,y
*/
void Union(subset subsets[], int x, int y);

/* 
funkce algoritmus hledajici mst 
*/
edge* KruskalMST(graph* graph_temp, vertex *vertex_data, uint *edge_mst_len);

#endif