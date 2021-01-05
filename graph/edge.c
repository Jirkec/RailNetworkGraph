#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "edge.h"
#include "usefc.h"

edge *edge_load(const char filename[], uint *datasize){
    FILE *f = NULL;
	char line[LINE_LEN], *word;
	edge *temp = NULL;
	uint act_idx = 0, max_idx = BLOCK_LEN, comp_cnt, duplicated=0, line_id = 0;

	if (!filename || !strcmp(filename, "")){
        printf("Invalid edge filename.\n");
        return NULL;
    } 
    
	f = fopen(filename, "r");
	if (!f){ 
        printf("Cannot open edge file.\n");
		return NULL;
    }

	temp = (edge *) malloc(BLOCK_LEN * sizeof(edge));
	if (!temp) {
		fclose(f);
		return NULL;
	}	

	while (fgets(line, LINE_LEN, f)) {        
        duplicated = 0;
      
        if(line_id==0 && !strstr(line, EDGE_FILE_HEADER)){       
                printf("Invalid edge file.\n");
                fclose(f);
                free(temp);
                return NULL;                       
        }

        if(line_id==0){
            line_id++;
            continue;
        }

		memset((void *) &temp[act_idx], 0, sizeof(edge));
 	 
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
                                duplicated = 1;
                            }
                            break;
                            
					case 2: word[strlen(word)-1] = 0; 
                            strcpy(temp[act_idx].sname, word); break;
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
			edge *t = NULL;
			t = (edge *) realloc(temp, (max_idx + BLOCK_LEN) * sizeof(edge));
			if (t) {
				temp = t;
				max_idx += BLOCK_LEN;
			}
			else break;
		}

        line_id++;
	}
	
	if (datasize) *datasize = act_idx;
	fclose(f);
	
	return temp;
}

int edge_compar_fn(const void *p1, const void *p2){
    uint id1, id2;
    id1 = ((edge *) p1)->id;
    id2 = ((edge *) p2)->id;

    if(id1 == id2)
        return 0;

    if(id1 < id2)
        return -1;

    if(id1 > id2)
        return 1;

    return 0;
}

void edge_print(edge *edge_data, uint datasize){
    uint i;

    printf("Vypis nactenych vrcholu:\n");
    for(i=0;i<datasize;i++){
        printf("i: %d | id: %d | wkt: %s | sname: %s\n", i, edge_data[i].id, edge_data[i].wkt, edge_data[i].sname);
    }
}