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

static int calcPoly() {

	char tmp[strlen(input) + 1];
	int in = 0;

	while(in != strlen(input)) {
		int out = 0;
		in = strlen(input);
		memset(tmp, 0, sizeof(tmp));

		for(int i = 0; i < strlen(input); i++) 
			if(((input[i] < 97 && input[i+1] >= 97) || (input[i] >= 97 && input[i+1] < 97)) && abs(input[i] - input[i+1]) == 32)
				i++;
			else
				tmp[out++] = input[i];

		strcpy(input, tmp);
	}

	return strlen(input);
}

/*##########################
# Function to solve part A #
##########################*/
void get5a(char * f) {

	if(!getInput(f))
		return;

	
	printf("5a: %d\n", calcPoly());

	free(input);
	input = NULL;
}


/*##########################
# Function to solve part B #
##########################*/
void get5b(char *f) {

	if(!getInput(f))
		return;

	char backup[strlen(input) + 1];
	char tmp[strlen(input) + 1];
	strcpy(backup, input);
	int out = 0xFFFFFF;

	for(int i = 65; i < 91; i++) {
		memset(tmp, 0, sizeof(tmp));
		int cnt = 0;
		for(int j = 0; j < strlen(input); j++)
			if(input[j] != i && input[j] != i+32)
				tmp[cnt++] = input[j];

		strcpy(input, tmp);
		int get = calcPoly();
		if(get < out)
			out = get;
		strcpy(input, backup);

	}	
	
	printf("5b: %d\n\n", out);

	free(input);
	input = NULL;
}


