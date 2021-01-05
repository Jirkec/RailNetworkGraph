#include <stdio.h>
#include <stdlib.h>
#include "usefc.h"
#include "vertex.h"

#define LINE_LEN 256

int main(int argc, char *argv[]) {
/* osetreni argumentu */
	if(argc < 4){
		printf("Error: Invalid argument count!\n");
		return EXIT_FAILURE;
	}

	int v_argument_index, e_argument_index, mst_argument_index, mrn_argument_index;
	
	v_argument_index = inArrayString(argc, argv, "-v");
	e_argument_index = inArrayString(argc, argv, "-e");
	mst_argument_index = inArrayString(argc, argv, "-mst");
	mrn_argument_index = inArrayString(argc, argv, "-mrn");
	 
	if(v_argument_index<0 || e_argument_index<0){
		printf("Error: Invalid argument count!\n");
		return EXIT_FAILURE;
	}

/* nacteni vrcholu */
	FILE *v_file = NULL;
	char v_file_line[LINE_LEN];

	v_file = fopen(argv[v_argument_index+1], "r");
	if(!v_file){
		printf("Invalid vertex file.\n");
		return 1;
	}
	while(!feof(v_file)){
		fgets(v_file_line, LINE_LEN, v_file);
		printf("%s\n", v_file_line);break;
	}
	fclose(v_file);

/* nacteni hran */
	FILE *e_file = NULL;
	char e_file_line[LINE_LEN];

	e_file = fopen(argv[e_argument_index+1], "r");
	if(!e_file){
		printf("Invalid edge file.\n");
		return 2;
	}
	while(!feof(e_file)){
		fgets(e_file_line, LINE_LEN, e_file);
		printf("%s\n", e_file_line);break;
	}
	fclose(v_file);
}