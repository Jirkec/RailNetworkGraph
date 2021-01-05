#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"

vertex *vertex_load(const char filename[], uint *datasize){
    FILE *f = NULL;
	char line[LINE_LEN], *word;
	vertex *temp = NULL;
	uint act_idx = 0, max_idx = BLOCK_LEN, comp_cnt, duplicated=0;
	
	if (!filename || !strcmp(filename, "")) return NULL;
	
	f = fopen(filename, "r");
	if (!f){ 
        printf("Invalid vertex file.\n");
		return NULL;
    }

	temp = (vertex *) malloc(BLOCK_LEN * sizeof(vertex));
	if (!temp) {
		fclose(f);
		return NULL;
	}
	

	while (fgets(line, LINE_LEN, f)) {
        if(act_idx==0 && strcmp(line, VERTEX_FILE_HEADER)!=0){
            printf("Invalid vertex file.\n");
            fclose(f);
            free(temp);
            return NULL;
        }

		memset((void *) &temp[act_idx], 0, sizeof(vertex));
	
		word = strtok(line, DELIMITERS);
		comp_cnt = 0;
		while (word) {
			if (strcmp(word, "NULL")) {                    
				switch (comp_cnt) {
					case 0: strcpy(temp[act_idx].wkt, word); break;
					case 1: if(act_idx==0 || (uint)atoi(word) != temp[act_idx-1].id){
                                temp[act_idx].id = atoi(word); 
                                duplicated = 0;
                            }else{
                                free((void *) &temp[act_idx]);
                                duplicated = 1;
                            }
                            break;
                            
					case 2: strcpy(temp[act_idx].sname, word); break;
				}
			}

            if(duplicated)
                break;
			
			/*printf("line %d: %s\n", act_idx, word);*/
			word = strtok(NULL, DELIMITERS);
			comp_cnt++;
		}
		if(!duplicated)
		    act_idx++;

		if (act_idx >= max_idx) {
			vertex *t = NULL;
			t = (vertex *) realloc(temp, (max_idx + BLOCK_LEN) * sizeof(vertex));
			if (t) {
				temp = t;
				max_idx += BLOCK_LEN;
			}
			else break;
		}
	}
	
	if (datasize) *datasize = act_idx;
	fclose(f);
	
	return temp;
}

int vertex_compar_fn(const void *p1, const void *p2){
    uint id1, id2;
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