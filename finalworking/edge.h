#ifndef __EDGE_H__
#define __EDGE_H__

#include "usefc.h"

/* delka radky souboru */
#define EDGE_LINE_LEN 13000
/* veliksot o kterou se bude dynamicky zvetsovat pamet pro hrany */
#define EDGE_BLOCK_LEN 128
/* velikost retezce cntryname */
#define CNTRYNAME_LEN 64
/* oddelovac atribtuu v souboru */
#define EDGE_DELIMITERS ","
/* hlavicka soubrou hran */
#define EDGE_FILE_HEADER "WKT,id,nation,cntryname,source,target,clength"

/*
struktura hrany
*/
typedef struct theedge {
    char *wkt_pointer;
    uint id;
    uint nation;
    char cntryname[CNTRYNAME_LEN];
    uint source;
    uint target;
    real clength;
} edge; 

/*
nacte hrany ze souboru
@param const char filename[] - nazev souboru
@param uint *datasize - ukazatel na promenou velikosti dat
*/
edge *edge_load(const char filename[], uint *datasize);
/* 
porovnavaci fce podle id vzestupne
*/
int edge_compar_fn_by_id(const void *p1, const void *p2);
/* 
porovnavaci fce podle clen sestupne
*/
int edge_compar_fn_by_clen(const void *p1, const void *p2);
/* 
porovnavaci fce podle clen vzestupne
*/
int edge_compar_fn_by_id_down(const void *p1, const void *p2);
/* 
porovnavaci fce podle clen sestupne
*/
int edge_compar_fn_by_clen_down(const void *p1, const void *p2);
/* 
vypis hran
*/
void edge_print(edge *edge_data, uint datasize);
/*
export hran do souboru podle pozadavku parametru -mst
*/
void edge_export_mst(edge *edge_data, uint datasize, char *filename);
/*
export hran do souboru podle pozadavku parametru -mrn
*/
void edge_export_mrn(edge *edge_data, uint datasize, char *filename);

#endif