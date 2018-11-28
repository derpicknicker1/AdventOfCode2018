/*
PLACE INSTRUCTIONS HERE
*/

#include "advent.h"

static char *input = NULL;


/*##########################
# Get input data from file #
##########################*/
static int getInput(char *f) {
	char * line = NULL;
    size_t l = 0;

	FILE *file=fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}
	
	// This is a example for reading ONE line from file.
	// Change it to the needed method (multiline, nodes, etc.)
	if( getline(&line, &l, file) != -1 ) {
		input = (char*)realloc(input, strlen(line) + 1);
		strcpy(input,line);
	}
	else 
		return 0;

	free(line);
	fclose(file);
	return 1;
}


/*##########################
# Function to solve part A #
##########################*/
void get0a(char * f) {

	if(!getInput(f))
		return;

	/* Process data for part A here */

	printf("0a: %s\n", input);

	free(input);
	input = NULL;
}


/*##########################
# Function to solve part B #
##########################*/
void get0b(char *f) {

	if(!getInput(f))
		return;

	/* Process data for part B here */	
	
	printf("0b: %s\n\n", input);

	free(input);
	input = NULL;
}