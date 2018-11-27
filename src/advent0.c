/*
PLACE INSTRUCTIONS HERE
*/

#include "advent.h"
#define DAY 0

static char *input = NULL;

static int getInput(char *f) {
	char * line = NULL;
    size_t l = 0;

	FILE *file=fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}
	
	while( getline(&line, &l, file) != -1 ) {
		input = (char*)realloc(input, strlen(line) + 1);
		strcpy(input,line);
	}

	free(line);
	fclose(file);
	return 1;
}

void get0a(char * f) {

	if(!getInput(f))
		return;

	/*
		Process data for part A
	*/

	free(input);
	input = NULL;

	printf("0a: %s\n", "Example 0a");
}

void get0b(char *f) {

	if(!getInput(f))
		return;

	/*
		Process data for part B
	*/

	free(input);
	input = NULL;	
	
	printf("0b: %s\n\n", "Example 0b");
}