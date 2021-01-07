#ifndef __EDGE_H__
#define __EDGE_H__

#include "usefc.h"

#define EDGE_LINE_LEN 13000
#define EDGE_BLOCK_LEN 128
#define EDGE_DATA_LINE_LEN 128
#define CNTRYNAME_LEN 64
#define EDGE_DELIMITERS ","
#define EDGE_FILE_HEADER "WKT,id,nation,cntryname,source,target,clength"

typedef struct theedge {
    char *wkt_pointer;
    uint id;
    uint nation;
    char cntryname[CNTRYNAME_LEN];
    uint source;
    uint target;
    real clength;
} edge; 

edge *edge_load(const char filename[], uint *datasize);
int edge_compar_fn_by_id(const void *p1, const void *p2);
int edge_compar_fn_by_clen(const void *p1, const void *p2);
void edge_print(edge *edge_data, uint datasize);
void edge_export_mst(edge *edge_data, uint datasize, char *filename);

#endif