/*
--- Day 5: Alchemical Reduction ---
You've managed to sneak in to the prototype suit manufacturing lab. The Elves are making decent progress, but are still struggling with the suit's size reduction capabilities.

While the very latest in 1518 alchemical technology might have solved their problem eventually, you can do better. You scan the chemical composition of the suit's material and discover that it is formed by extremely long polymers (one of which is available as your puzzle input).

The polymer is formed by smaller units which, when triggered, react with each other such that two adjacent units of the same type and opposite polarity are destroyed. Units' types are represented by letters; units' polarity is represented by capitalization. For instance, r and R are units with the same type but opposite polarity, whereas r and s are entirely different types and do not react.

For example:

In aA, a and A react, leaving nothing behind.
In abBA, bB destroys itself, leaving aA. As above, this then destroys itself, leaving nothing.
In abAB, no two adjacent units are of the same type, and so nothing happens.
In aabAAB, even though aa and AA are of the same type, their polarities match, and so nothing happens.
Now, consider a larger example, dabAcCaCBAcCcaDA:

dabAcCaCBAcCcaDA  The first 'cC' is removed.
dabAaCBAcCcaDA    This creates 'Aa', which is removed.
dabCBAcCcaDA      Either 'cC' or 'Cc' are removed (the result is the same).
dabCBAcaDA        No further actions can be taken.
After all possible reactions, the resulting polymer contains 10 units.

How many units remain after fully reacting the polymer you scanned? (Note: in this puzzle and others, the input is large; if you copy/paste your input, make sure you get the whole thing.)

Your puzzle answer was 10766.

--- Part Two ---
Time to improve the polymer.

One of the unit types is causing problems; it's preventing the polymer from collapsing as much as it should. Your goal is to figure out which unit type is causing the most problems, remove all instances of it (regardless of polarity), fully react the remaining polymer, and measure its length.

For example, again using the polymer dabAcCaCBAcCcaDA from above:

Removing all A/a units produces dbcCCBcCcD. Fully reacting this polymer produces dbCBcD, which has length 6.
Removing all B/b units produces daAcCaCAcCcaDA. Fully reacting this polymer produces daCAcaDA, which has length 8.
Removing all C/c units produces dabAaBAaDA. Fully reacting this polymer produces daDA, which has length 4.
Removing all D/d units produces abAcCaCBAcCcaA. Fully reacting this polymer produces abCBAc, which has length 6.
In this example, removing all C/c units was best, producing the answer 4.

What is the length of the shortest polymer you can produce by removing all units of exactly one type and fully reacting the result?

Your puzzle answer was 6538.
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


