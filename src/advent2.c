/*
--- Day 2: Inventory Management System ---
You stop falling through time, catch your breath, and check the screen on the device. "Destination reached. Current Year: 1518. Current Location: North Pole Utility Closet 83N10." You made it! Now, to find those anomalies.

Outside the utility closet, you hear footsteps and a voice. "...I'm not sure either. But now that so many people have chimneys, maybe he could sneak in that way?" Another voice responds, "Actually, we've been working on a new kind of suit that would let him fit through tight spaces like that. But, I heard that a few days ago, they lost the prototype fabric, the design plans, everything! Nobody on the team can even seem to remember important details of the project!"

"Wouldn't they have had enough fabric to fill several boxes in the warehouse? They'd be stored together, so the box IDs should be similar. Too bad it would take forever to search the warehouse for two similar box IDs..." They walk too far away to hear any more.

Late at night, you sneak to the warehouse - who knows what kinds of paradoxes you could cause if you were discovered - and use your fancy wrist device to quickly scan every box and produce a list of the likely candidates (your puzzle input).

To make sure you didn't miss any, you scan the likely candidate boxes again, counting the number that have an ID containing exactly two of any letter and then separately counting those with exactly three of any letter. You can multiply those two counts together to get a rudimentary checksum and compare it to what your device predicts.

For example, if you see the following box IDs:

abcdef contains no letters that appear exactly two or three times.
bababc contains two a and three b, so it counts for both.
abbcde contains two b, but no letter appears exactly three times.
abcccd contains three c, but no letter appears exactly two times.
aabcdd contains two a and two d, but it only counts once.
abcdee contains two e.
ababab contains three a and three b, but it only counts once.
Of these box IDs, four of them contain a letter which appears exactly twice, and three of them contain a letter which appears exactly three times. Multiplying these together produces a checksum of 4 * 3 = 12.

What is the checksum for your list of box IDs?

Your puzzle answer was 7936.

--- Part Two ---
Confident that your list of box IDs is complete, you're ready to find the boxes full of prototype fabric.

The boxes will have IDs which differ by exactly one character at the same position in both strings. For example, given the following box IDs:

abcde
fghij
klmno
pqrst
fguij
axcye
wvxyz
The IDs abcde and axcye are close, but they differ by two characters (the second and fourth). However, the IDs fghij and fguij differ by exactly one character, the third (h and u). Those must be the correct boxes.

What letters are common between the two correct box IDs? (In the example above, this is found by removing the differing character from either ID, producing fgij.)

Your puzzle answer was lnfqdscwjyteorambzuchrgpx.
*/

#include "advent.h"

static char **input;
static int lines;


/*##########################
# Get input data from file #
##########################*/
static int getInput(char *f) {
	char * line = NULL;
	lines = 0;
	input = NULL;
    size_t l = 0;

	FILE *file=fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}
	
	while( getline(&line, &l, file) != -1 ) {
		input = (char**)realloc(input, ++lines * sizeof(char*));
		input[lines-1] = (char*)malloc(strlen(line) * sizeof(char));
		memcpy(input[lines-1], line, strlen(line));
	}

	free(line);
	fclose(file);
	return 1;
}


/*##########################
# Function to solve part A #
##########################*/
void get2a(char * f) {

	if(!getInput(f))
		return;

	int cnt[26] = {};
	int two = 0, three = 0;

	for(int i = 0; i < lines; i++){

		int tmp2 = 0, tmp3 = 0;
		for(int j = 0; j < strlen(input[i]) && input[i][j] != '\n'; j++)
			cnt[input[i][j]-97]++;
		for(int j = 0; j < 26; j++){
			if(cnt[j] == 2)
				tmp2++;
			if(cnt[j] == 3)
				tmp3++;
			cnt[j] = 0;
		}
		if(tmp2)
			two++;
		if(tmp3)
			three++;
	}

	printf("2a: %d\n", two * three);

	for(int i = 0; i < lines; i++)
		free(input[i]);
	free(input);

}


/*##########################
# Function to solve part B #
##########################*/
void get2b(char *f) {

	if(!getInput(f))
		return;

	char *result = NULL;

	for(int i = 0; i < lines; i++){
		for(int j = i+1; j < lines; j++){
			int diff = 0;
			for(int x = 0; x < strlen(input[i]) && input[i][x] != '\n' && diff < 2; x++)
				if(input[i][x] != input[j][x])
					diff++;
			if(diff == 1) {
				int pos = 0;
				result = malloc( (strlen(input[i]) + 1) * sizeof(char));
				for(int x = 0; x < strlen(input[i]) && input[i][x] != '\n'; x++)
					if(input[i][x] == input[j][x])
						result[pos++] = input[i][x];
				result[pos] = '\0';
				i = lines;
				break;
			}
		}
	}
	printf("2b: %s\n\n", result);
	for(int i = 0; i < lines; i++)
		free(input[i]);
	free(input);
	free(result);

}