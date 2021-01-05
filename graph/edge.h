#ifndef __EDGE_H__
#define __EDGE_H__

#include "usefc.h"

#define LINE_LEN 256
#define BLOCK_LEN 16
#define EDGE_WKT_LEN 128
#define CNTRYNAME_LEN 64
#define DELIMITERS ","
#define EDGE_FILE_HEADER "WKT,id,nation,cntryname,source,target,clength"

typedef struct theedge {
	char wkt[EDGE_WKT_LEN];
    uint id;
    uint nation;
    char cntryname[CNTRYNAME_LEN];
    uint source;
    uint target;
    uint clength;
} edge; 

edge *edge_load(const char filename[], uint *datasize);
int edge_compar_fn(const void *p1, const void *p2);
void edge_print(edge *edge_data, uint datasize);

#endif