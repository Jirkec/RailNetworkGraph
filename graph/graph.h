#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "usefc.h"
#include "edge.h"
#include "vertex.h"

typedef struct thegraph {
    uint vertex_dlen, edge_dlen;
    edge *edges;
} graph;

typedef struct thesubset {
    uint parent;
    int rank;
} subset;

graph* createGraph(uint vertex_dlen, uint edge_dlen, edge *edges);
uint find(subset subsets[], uint i);
void Union(subset subsets[], int x, int y);
edge* KruskalMST(graph* graph_temp, vertex *vertex_data, uint *edge_mst_len);

#endif