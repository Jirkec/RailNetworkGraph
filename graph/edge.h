#ifndef __EDGE_H__
#define __EDGE_H__

#include "usefc.h"

#define LINE_LEN 256
#define BLOCK_LEN 16
#define DELIMITERS ","
#define EDGE_FILE_HEADER "WKT,id,sname"

typedef struct theedge {
	char wkt[64];
    uint id;
    char sname[64];
} edge; 

edge *edge_load(const char filename[], uint *datasize);
int edge_compar_fn(const void *p1, const void *p2);
void edge_print(edge *edge_data, uint datasize);

#endif