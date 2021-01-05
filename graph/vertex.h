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

vertex *load(const char filename[], uint *datasize);
int compar_fn(const void *p1, const void *p2);

#endif