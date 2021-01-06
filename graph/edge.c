#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "edge.h"
#include "usefc.h"

edge *edge_load(const char filename[], uint *datasize){
    FILE *f = NULL;
	char line[LINE_LEN], *word;
	edge *temp = NULL;
	uint act_idx = 0, max_idx = BLOCK_LEN, comp_cnt, ignore=0, line_id = 0, i, atoied_word;

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
        ignore = 0;
      
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
					case 1: strcat(temp[act_idx].wkt, ","); 
							strcat(temp[act_idx].wkt, word); 
							break;

					case 2: atoied_word = (uint)atoi(word);
							for(i=0;i<act_idx;i++){
								if(temp[i].id == atoied_word){
									ignore = 1;
									break;
								}
							}
							if(!ignore)
								temp[act_idx].id = atoied_word;
                            break;
                            
					case 3: temp[act_idx].nation = atoi(word); break;
					case 4: strcpy(temp[act_idx].cntryname, word); break;
					case 5: temp[act_idx].source = atoi(word); break;
					
					case 6: atoied_word = (uint)atoi(word);
							if(!ignore && temp[act_idx].source != atoied_word){
								for(i=0;i<act_idx;i++){
									if(	(temp[i].source == temp[act_idx].source && temp[i].target == atoied_word)
										||
										(temp[i].source == atoied_word 			&& temp[i].target == temp[act_idx].source)
									){
										ignore = 1;
									}
								}

								if(!ignore)
									temp[act_idx].target = atoied_word; 
							}else{
								ignore = 1;
							}							
							break;

					case 7: atoied_word = (uint)atoi(word);
							if(!ignore && atoied_word > 0) {
								temp[act_idx].clength = atoied_word; 
							}else{
								ignore = 1;
							}
							break;
				}
			}
            if(ignore)
                break;
			
			/*printf("line %d: %s\n", act_idx, word);*/
			word = strtok(NULL, DELIMITERS);
			comp_cnt++;
		}

        
		if(!ignore)
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

    printf("List of loaded edges:\n");
    for(i=0;i<datasize;i++){
        printf("i: %d | id: %d | wkt: %s | nation: %d | cntryname: %s | source: %d | target: %d | clength: %d |\n", i, edge_data[i].id, edge_data[i].wkt, edge_data[i].nation, edge_data[i].cntryname, edge_data[i].source, edge_data[i].target, edge_data[i].clength);
    }
}