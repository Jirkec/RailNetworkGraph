#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"
#include "usefc.h"

/*
nacte vrcholy ze souboru
@param const char filename[] - nazev souboru
@param uint *datasize - ukazatel na promenou velikosti dat
*/
vertex *vertex_load(const char filename[], uint *datasize){
    FILE *f = NULL;
	char line[VERTEX_LINE_LEN], *word;
	vertex *temp = NULL;
	uint act_idx = 0, max_idx = VERTEX_BLOCK_LEN, comp_cnt, ignore=0, line_id = 0;

	/* osetreni parametru */
	if (!filename || !strcmp(filename, "")){
        printf("Invalid vertex filename.\n");
        return NULL;
    } 
    
	/* otevreni soubru */
	f = fopen(filename, "r");
	if (!f){ 
        printf("Cannot open vertex file.\n");
		return NULL;
    }

	/* pocatecni alokovani pameti */
	temp = (vertex *) malloc(VERTEX_BLOCK_LEN * sizeof(vertex));
	if (!temp) {
		printf("Memory allocation failed in vertex_load()!\n");
		fclose(f);
		return NULL;
	}	

	/* cteni souboru */
	while (fgets(line, VERTEX_LINE_LEN, f)) {        
        ignore = 0;
      
	  /* overovani hlavicky souboru */
        if(line_id==0 && !strstr(line, VERTEX_FILE_HEADER)){       
                printf("Invalid vertex file.\n");
                fclose(f);
                free(temp);
                return NULL;                       
        }
        if(line_id==0){
            line_id++;
            continue;
        }
		/* priprava pametu */
		memset((void *) &temp[act_idx], 0, sizeof(vertex));
 	 
	  	/* nacitani atributu z radky*/
		word = strtok(line, VERTEX_DELIMITERS);
		comp_cnt = 0;
		while (word) {
			if (strcmp(word, "NULL")) {                    
				switch (comp_cnt) {
					case 0: strcpy(temp[act_idx].wkt, word); break;
					case 1: if(act_idx==0 || (uint)atoi(word) != temp[act_idx-1].id){
                                temp[act_idx].id = atoi(word); 
                            }else{
                                ignore = 1;
                            }
                            break;
                            
					case 2: word[strlen(word)-1] = 0; 
                            strcpy(temp[act_idx].sname, word); 
                            break;
				}
			}
            if(ignore)
                break;
			
			word = strtok(NULL, VERTEX_DELIMITERS);
			comp_cnt++;
		}

        /* zajisti ignorovani vrcholu */
		if(!ignore)
		    act_idx++;

		/* dynamicke alokovani */ 
		if (act_idx >= max_idx) {
			vertex *t = NULL;
			t = (vertex *) realloc(temp, (max_idx + VERTEX_BLOCK_LEN) * sizeof(vertex));
			if (t) {
				temp = t;
				max_idx += VERTEX_BLOCK_LEN;
			}
			else break;
		}

        line_id++;
	}
	
	if (datasize) *datasize = act_idx;
	fclose(f);
	
	return temp;
}

/*
seradi vrcholy podle id vzestupne
*/
int vertex_compar_fn(const void *p1, const void *p2){
    uint id1, id2;

	/* osetreni parametru */
	if(!p1 || !p2){
		printf("Wrong params given to vertex_compar_fn()!\n");
		return 0;
	}

    id1 = ((vertex *) p1)->id;
    id2 = ((vertex *) p2)->id;

    if(id1 == id2)
        return 0;

    if(id1 < id2)
        return -1;

    if(id1 > id2)
        return 1;

    return 0;
}

/*
vypise vrcholy
*/
void vertex_print(vertex *vertex_data, uint datasize){
    uint i;
	
	/* osetreni parametru */
	if(!vertex_data || datasize<=0){
		printf("Wrong params given to vertex_print()!\n");
		return;
	}

    printf("List of loaded vertexes:\n");
    for(i=0;i<datasize;i++){
        printf("i: %d | id: %d | wkt: %s | sname: %s\n", i, vertex_data[i].id, vertex_data[i].wkt, vertex_data[i].sname);
    }
}

/*
najde index vrcholy v poli podle atributu id
@param vertex *vertex_data - vrcholy
@param uint datasize - pocet vrcholu
@param uint id - hledane id
*/
int vertex_get_key_by_id(vertex *vertex_data, uint datasize, uint id){
	uint i;
	
	/* osetreni parametru */
	if(!vertex_data || datasize<=0 || id<=0 ){
		printf("Wrong params given to vertex_get_key_by_id()!\n");
		return -1;
	}

	for(i =0; i<datasize;i++){
		if(vertex_data[i].id == id)
			return i;
	}
	return -1;
}