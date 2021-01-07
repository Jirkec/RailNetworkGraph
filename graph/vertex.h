#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "usefc.h"

#define VERTEX_LINE_LEN 256
#define VERTEX_BLOCK_LEN 128
#define VERTEX_WKT_LEN 128
#define SNAME_LEN 64
#define VERTEX_DELIMITERS ","
#define VERTEX_FILE_HEADER "WKT,id,sname"


typedef struct thevertex {
	char wkt[VERTEX_WKT_LEN];
    uint id;
    char sname[SNAME_LEN];
} vertex; 

vertex *vertex_load(const char filename[], uint *datasize);
int vertex_compar_fn(const void *p1, const void *p2);
void vertex_print(vertex *vertex_data, uint datasize);
int vertex_get_key_by_id(vertex *vertex_data, uint datasize, uint id);

#endif