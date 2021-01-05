#ifndef __VERTEX_H__
#define __VERTEX_H__


#define LINE_LEN 256
#define BLOCK_LEN 16
#define DELIMITERS ","
#define VERTEX_FILE_HEADER "WKT,id,sname"

typedef unsigned int uint;

typedef struct thevertex {
	char wkt[64];
    uint id;
    char sname[64];
} vertex; 

vertex *vertex_load(const char filename[], uint *datasize);
int vertex_compar_fn(const void *p1, const void *p2);
void vertex_print(vertex *vertex_data, uint datasize);

#endif