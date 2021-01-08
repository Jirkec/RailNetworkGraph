#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "edge.h"
#include "usefc.h"

/*
nacte hrany ze souboru
@param const char filename[] - nazev souboru
@param uint *datasize - ukazatel na promenou velikosti dat
*/
edge *edge_load(const char filename[], uint *datasize){
    FILE *f = NULL;
	char line[EDGE_LINE_LEN], *word, wkt[EDGE_LINE_LEN], *wkt_end;
	edge *temp = NULL;
	uint act_idx = 0, max_idx = EDGE_BLOCK_LEN, comp_cnt, ignore=0, line_id = 0, i, atoied_word, invalid_case;
	real atofed_word;

/* osetreni parametru */
	if (!filename || !strcmp(filename, "")){
        printf("Invalid edge filename.\n");
        return NULL;
    } 
    
/* otevreni souboru */	
	f = fopen(filename, "r");
	if (!f){ 
        printf("Cannot open edge file.\n");
		return NULL;
    }

/* zacatecni alokovani pameti pro hrany - prvnotne pocitam se 16 hranama, potom dynamicky rozsiruji */
	temp = (edge *) malloc(EDGE_BLOCK_LEN * sizeof(edge));	
	if (!temp) {
		printf("Memory allocation failed in edge_load()!\n");
		fclose(f);
		return NULL;
	}

/* cteni ze souboru */
	while (fgets(line, EDGE_LINE_LEN, f)) { 
		int act_wkt_len = 0;       
        ignore = 0;
      
	  /* osetreni hlavicky souboru */
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
		if(strlen(line)>0){
 
		/* priprava pameti pro aktualni hranu v cyklu */
		memset((void *) &temp[act_idx], 0, sizeof(edge));
	
		/* WKT handeling dynamic */
		wkt_end = strchr(line+1, '"');												/* nalezeni konce wkt (+1, abych vynechal prvni uvozovky) *//*printf("3line_id:%d\n",line_id);*/
		act_wkt_len = wkt_end-line+1;												/* velikost wkt (+1, abych vzal i posledni posledni uvozovky) */
		strncpy(wkt, line, act_wkt_len);											/* vykopirovani wkt z line (+1, abych vzal i posledni posledni uvozovky) *//*printf("4\n");*/
		wkt[act_wkt_len]='\0';														/* ukonceni wkt retezce *//*printf("5\n");*/
		temp[act_idx].wkt_pointer = (char *)malloc((act_wkt_len+1) * sizeof(char));	/* alokovani pameti pro wkt */	
		if(!temp[act_idx].wkt_pointer){
			printf("Memory allocation failed in edge_load()!\n");
            fclose(f);
            free(temp);
			return NULL;
		}
		strncpy(temp[act_idx].wkt_pointer, wkt, act_wkt_len);						/* kopirovani wkt do wkt hrany *//*printf("7\n");*/
		temp[act_idx].wkt_pointer[act_wkt_len] = '\0';

		/* parsovani radky podle EDGE_DELIMITERS  */		
		word = strtok(wkt_end+2, EDGE_DELIMITERS);	/* +2 abych preskocil uvozovky a carku -> prvni znak je hodnota id */							
		comp_cnt = 0;
		
		while (word) {		
			invalid_case=0;

			/* naplneni atributu hrany aktualniho indexu */
			if (strcmp(word, "NULL")) {   
				switch (comp_cnt) {
					case 0: atoied_word = (uint)atoi(word);
							for(i=0;i<act_idx;i++){
								if(temp[i].id == atoied_word){
									ignore = 1;
									break;
								}
							}
							if(!ignore)
								temp[act_idx].id = atoied_word;
                            break;
                            
					case 1: temp[act_idx].nation = atoi(word); break;
					case 2: strcpy(temp[act_idx].cntryname, word); break;
					case 3: temp[act_idx].source = atoi(word); break;
					
					case 4: atoied_word = (uint)atoi(word);
							/* source a target se nerovnaji */
							if(!ignore && temp[act_idx].source != atoied_word){
								for(i=0;i<act_idx;i++){
									/* existuje spojeni */
									if(	(temp[i].source == temp[act_idx].source && temp[i].target == atoied_word)
										||
										(temp[i].source == atoied_word 			&& temp[i].target == temp[act_idx].source))
									{
										ignore = 1;
									}
								}

								if(!ignore)
									temp[act_idx].target = atoied_word; 
							}else{
								ignore = 1;
							}							
							break;

					case 5: atofed_word = (real)atof(word);
							if(!ignore && atofed_word > 0) {
								temp[act_idx].clength = atofed_word; 
							}else{
								ignore = 1;
							}
							break;
					default: invalid_case=1; break;
				}
			}
			/* zajisteni ignorovani atributu ve slove word */
            if(ignore || invalid_case){
                break;
			}
			
			word = strtok(NULL, EDGE_DELIMITERS);
			comp_cnt++;
		}

		if(ignore){
			free(temp[act_idx].wkt_pointer);
		}

        /* ignorovani cele hrany - bude prepsana dalsi hranou */
		if(!ignore)
		    act_idx++;

		/* dynamicke alokovani pameti */
		if (act_idx >= max_idx) {
			edge *t = NULL;
			t = (edge *) realloc(temp, (max_idx + EDGE_BLOCK_LEN) * sizeof(edge));
			if (t) {
				temp = t;
				max_idx += EDGE_BLOCK_LEN;
			}
			else break;
		}

        line_id++;
		}
	}
	
	if (datasize) *datasize = act_idx;
	fclose(f);
	
	return temp;
}

/* 
porovnavaci fce podle id vzestupne
*/
int edge_compar_fn_by_id(const void *p1, const void *p2){
    uint id1, id2;

	/* osetreni parametru */
	if(!p1 || !p2){
		printf("Wrong params given to edge_compar_fn_by_clen_down()!\n");
		return 0;
	}

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
/* 
porovnavaci fce podle id sestupne
*/
int edge_compar_fn_by_id_down(const void *p1, const void *p2){
    uint id1, id2;
	/* osetreni parametru */
	if(!p1 || !p2){
		printf("Wrong params given to edge_compar_fn_by_clen_down()!\n");
		return 0;
	}

    id1 = ((edge *) p1)->id;
    id2 = ((edge *) p2)->id;

    if(id1 == id2)
        return 0;

    if(id1 < id2)
        return 1;

    if(id1 > id2)
        return -1;

    return 0;
}
/* 
porovnavaci fce podle clen vzestupne
*/
int edge_compar_fn_by_clen(const void *p1, const void *p2)
{
    edge* a1;
    edge* b1;
	
	/* osetreni parametru */
	if(!p1 || !p2){
		printf("Wrong params given to edge_compar_fn_by_clen_down()!\n");
		return 0;
	}
	
    a1 = (edge*)p1;
    b1 = (edge*)p2;
    return a1->clength > b1->clength;
}
/* 
porovnavaci fce podle clen sestupne
*/
int edge_compar_fn_by_clen_down(const void *p1, const void *p2)
{	
    edge* a1;
    edge* b1;

	/* osetreni parametru */
	if(!p1 || !p2){
		printf("Wrong params given to edge_compar_fn_by_clen_down()!\n");
		return 0;
	}

    a1 = (edge*)p1;
    b1 = (edge*)p2;
    return a1->clength < b1->clength;
}

/* 
vypis hran
*/
void edge_print(edge *edge_data, uint datasize){
    uint i;

	/* osetreni parametru */
	if(!edge_data || datasize<=0){
		printf("Wrong params given to edge_print()!\n");
		return;
	}

    printf("List of loaded edges:\n");
    for(i=0;i<datasize;i++){
        printf("i: %d | id: %d | wkt: %s | nation: %d | cntryname: %s | source: %d | target: %d | clength: %f |\n", i, edge_data[i].id, edge_data[i].wkt_pointer, edge_data[i].nation, edge_data[i].cntryname, edge_data[i].source, edge_data[i].target, edge_data[i].clength);
    }
}

/*
export hran do souboru podle pozadavku parametru -mst
*/
void edge_export_mst(edge *edge_data, uint datasize, char *filename){
	FILE *fp;
	uint i;

	/* osetreni parametru */
	if(!edge_data || datasize<=0 || strlen(filename)<=0 ){
		printf("Wrong params given to edge_export_mst()!\n");
		return;
	}

	fp = fopen(filename, "w");
	if(!fp){
		printf("Cannot open file to write mst!\n");
		return;
	}	

	qsort(edge_data, datasize, sizeof(edge), edge_compar_fn_by_id_down);

	/* naplnenni souboru */
	fputs(EDGE_FILE_HEADER, fp);
	fputs("\n", fp);
	for(i=0;i<datasize;i++){
			fputs(edge_data[i].wkt_pointer, fp);			
			fputs(",", fp);

			fprintf(fp, "%u",edge_data[i].id);						
			fputs(",", fp);

			fprintf(fp, "%u",edge_data[i].nation);			
			fputs(",", fp);

			fprintf(fp, "%s", edge_data[i].cntryname);				
			fputs(",", fp);

			fprintf(fp, "%u",edge_data[i].source);			
			fputs(",", fp);

			fprintf(fp, "%u",edge_data[i].target);
			fputs(",", fp);
			
			fprintf(fp, "%f",edge_data[i].clength);	
			
		fputs("\n", fp);
		}
	fclose(fp);
}

/*
export hran do souboru podle pozadavku parametru -mrn
*/
void edge_export_mrn(edge *edge_data, uint datasize, char *filename){
	FILE *fp;
	uint i;
	uint new_id = 1;

	/* osetreni parametru */
	if(!edge_data || datasize<=0 || strlen(filename)<=0 ){
		printf("Wrong params given to edge_export_mrn()!\n");
		return;
	}

	/* otevreni souboru */
	fp = fopen(filename, "w");
	if(!fp){
		printf("Cannot open file to write mrn!\n");
		return;
	}	

	qsort(edge_data, datasize, sizeof(edge), edge_compar_fn_by_clen_down);

	/* naplnenni souboru */
	fputs(EDGE_FILE_HEADER, fp);
	fputs("\n", fp);
	for(i=0;i<datasize;i++){
			fputs(edge_data[i].wkt_pointer, fp);			
			fputs(",", fp);

			fprintf(fp, "%u",new_id);						
			fputs(",", fp);

			fprintf(fp, "%u",edge_data[i].nation);			
			fputs(",", fp);

			fprintf(fp, "%s", edge_data[i].cntryname);				
			fputs(",", fp);

			fprintf(fp, "%u",edge_data[i].source);			
			fputs(",", fp);

			fprintf(fp, "%u",edge_data[i].target);
			fputs(",", fp);
			
			fprintf(fp, "%.3f",edge_data[i].clength);	
			
		fputs("\n", fp);

		new_id++;
		}
	fclose(fp);
}