#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "usefc.h"

/* delka radky souboru */
#define VERTEX_LINE_LEN 256
/* veliksot o kterou se bude dynamicky zvetsovat pamet pro vrcholy */
#define VERTEX_BLOCK_LEN 128
/* velikost retezce wkt */
#define VERTEX_WKT_LEN 128
/* velikost retezce sname */
#define SNAME_LEN 64
/* oddelovac atribtuu v souboru */
#define VERTEX_DELIMITERS ","
/* hlavicka soubrou vrcholu */
#define VERTEX_FILE_HEADER "WKT,id,sname"

/*
struktura vrcholu
*/
typedef struct thevertex {
	char wkt[VERTEX_WKT_LEN];
    uint id;
    char sname[SNAME_LEN];
} vertex; 

/*
nacte vrcholy ze souboru
@param const char filename[] - nazev souboru
@param uint *datasize - ukazatel na promenou velikosti dat
*/
vertex *vertex_load(const char filename[], uint *datasize);

/*
seradi vrcholy podle id vzestupne
*/
int vertex_compar_fn(const void *p1, const void *p2);

/*
vypise vrcholy
*/
void vertex_print(vertex *vertex_data, uint datasize);

/*
najde index vrcholy v poli podle atributu id
@param vertex *vertex_data - vrcholy
@param uint datasize - pocet vrcholu
@param uint id - hledane id
*/
int vertex_get_key_by_id(vertex *vertex_data, uint datasize, uint id);

#endif