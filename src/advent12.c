/*
--- Day 12: Subterranean Sustainability ---
The year 518 is significantly more underground than your history books implied. Either that, or you've arrived in a vast cavern network under the North Pole.

After exploring a little, you discover a long tunnel that contains a row of small pots as far as you can see to your left and right. A few of them contain plants - someone is trying to grow things in these geothermally-heated caves.

The pots are numbered, with 0 in front of you. To the left, the pots are numbered -1, -2, -3, and so on; to the right, 1, 2, 3.... Your puzzle input contains a list of pots from 0 to the right and whether they do (#) or do not (.) currently contain a plant, the initial state. (No other pots currently contain plants.) For example, an initial state of #..##.... indicates that pots 0, 3, and 4 currently contain plants.

Your puzzle input also contains some notes you find on a nearby table: someone has been trying to figure out how these plants spread to nearby pots. Based on the notes, for each generation of plants, a given pot has or does not have a plant based on whether that pot (and the two pots on either side of it) had a plant in the last generation. These are written as LLCRR => N, where L are pots to the left, C is the current pot being considered, R are the pots to the right, and N is whether the current pot will have a plant in the next generation. For example:

A note like ..#.. => . means that a pot that contains a plant but with no plants within two pots of it will not have a plant in it during the next generation.
A note like ##.## => . means that an empty pot with two plants on each side of it will remain empty in the next generation.
A note like .##.# => # means that a pot has a plant in a given generation if, in the previous generation, there were plants in that pot, the one immediately to the left, and the one two pots to the right, but not in the ones immediately to the right and two to the left.
It's not clear what these plants are for, but you're sure it's important, so you'd like to make sure the current configuration of plants is sustainable by determining what will happen after 20 generations.

For example, given the following input:

initial state: #..#.#..##......###...###

...## => #
..#.. => #
.#... => #
.#.#. => #
.#.## => #
.##.. => #
.#### => #
#.#.# => #
#.### => #
##.#. => #
##.## => #
###.. => #
###.# => #
####. => #
For brevity, in this example, only the combinations which do produce a plant are listed. (Your input includes all possible combinations.) Then, the next 20 generations will look like this:

                 1         2         3     
       0         0         0         0     
 0: ...#..#.#..##......###...###...........
 1: ...#...#....#.....#..#..#..#...........
 2: ...##..##...##....#..#..#..##..........
 3: ..#.#...#..#.#....#..#..#...#..........
 4: ...#.#..#...#.#...#..#..##..##.........
 5: ....#...##...#.#..#..#...#...#.........
 6: ....##.#.#....#...#..##..##..##........
 7: ...#..###.#...##..#...#...#...#........
 8: ...#....##.#.#.#..##..##..##..##.......
 9: ...##..#..#####....#...#...#...#.......
10: ..#.#..#...#.##....##..##..##..##......
11: ...#...##...#.#...#.#...#...#...#......
12: ...##.#.#....#.#...#.#..##..##..##.....
13: ..#..###.#....#.#...#....#...#...#.....
14: ..#....##.#....#.#..##...##..##..##....
15: ..##..#..#.#....#....#..#.#...#...#....
16: .#.#..#...#.#...##...#...#.#..##..##...
17: ..#...##...#.#.#.#...##...#....#...#...
18: ..##.#.#....#####.#.#.#...##...##..##..
19: .#..###.#..#.#.#######.#.#.#..#.#...#..
20: .#....##....#####...#######....#.#..##.
The generation is shown along the left, where 0 is the initial state. The pot numbers are shown along the top, where 0 labels the center pot, negative-numbered pots extend to the left, and positive pots extend toward the right. Remember, the initial state begins at pot 0, which is not the leftmost pot used in this example.

After one generation, only seven plants remain. The one in pot 0 matched the rule looking for ..#.., the one in pot 4 matched the rule looking for .#.#., pot 9 matched .##.., and so on.

In this example, after 20 generations, the pots shown as # contain plants, the furthest left of which is pot -2, and the furthest right of which is pot 34. Adding up all the numbers of plant-containing pots after the 20th generation produces 325.

After 20 generations, what is the sum of the numbers of all pots which contain a plant?

Your puzzle answer was 3793.

--- Part Two ---
You realize that 20 generations aren't enough. After all, these plants will need to last another 1500 years to even reach your timeline, not to mention your future.

After fifty billion (50000000000) generations, what is the sum of the numbers of all pots which contain a plant?

Your puzzle answer was 4300000002414.
*/

#include "advent.h"

typedef struct Pattern {
	int a,b,c,d,e;
} Pattern;

static Pattern *pat = NULL;
static int *input = NULL;
static int cntP, iLen;


/*##########################
# Get input data from file #
##########################*/
static int getInput(char *f) {
	char * line = NULL;
    size_t l = 0;
    cntP = 0;

	FILE *file=fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}
	
	while( getline(&line, &l, file) != -1 ) {
		
		if(strstr(line, "initial state") != NULL){
			char start[150];
			sscanf(line, "initial state: %s", &start);
			iLen = strlen(start);
			input = realloc(input, iLen * sizeof(int));
			for(int i = 0; i < iLen; i++)
				input[i] = start[i] == '#' ? 1 : 0;
		}
		else if(strlen(line) > 3) {
			char p[6], s;
			sscanf(line, "%s => %c", &p, &s);
			if(s == '#') {
				pat = realloc(pat, ++cntP * sizeof(Pattern));
				pat[cntP - 1].a = p[0] == '#' ? 1 : 0;
				pat[cntP - 1].b = p[1] == '#' ? 1 : 0;
				pat[cntP - 1].c = p[2] == '#' ? 1 : 0;
				pat[cntP - 1].d = p[3] == '#' ? 1 : 0;
				pat[cntP - 1].e = p[4] == '#' ? 1 : 0;
			}
		}
	}
	
	free(line);
	fclose(file);
	return 1;
}


/*##########################
# Function to solve part A #
##########################*/
void get12a(char * f) {

	if(!getInput(f))
		return;

	int l = 3*iLen, row[l], tmp[l], p;
	memset(row, 0, sizeof(row));
	memcpy(row + iLen, input, iLen*sizeof(int));

	for(int i = 0; i < 20; i++) {

		memcpy(tmp, row, l*sizeof(int));
		
		for(int x = 2; x < l-2; x++) {
			for(p = 0; p < cntP; p++)
				if(row[x-2] == pat[p].a && row[x-1] == pat[p].b && row[x] == pat[p].c && row[x+1] == pat[p].d && row[x+2] == pat[p].e)
					break;
			tmp[x] = p < cntP ? 1 : 0;
		}
		
		memcpy(row, tmp, l*sizeof(int));
	}

	p = 0;
	for(int i = 0; i < l; i++) 
		p += row[i] ? (i - iLen) : 0;

	printf("12a: %d\n", p);

	free(input);
	input = NULL;
	free(pat);
	pat = NULL;
}


/*##########################
# Function to solve part B #
##########################*/
void get12b(char *f) {

	if(!getInput(f))
		return;

	int l = 4*iLen, row[l], tmp[l], p, i, oldSum = 0, period = 0, lastDiff = 0, sum;
	memset(row, 0, sizeof(row));
	memcpy(row + iLen, input, iLen*sizeof(int));

	for(i = 0; period < 10; i++) {

		memcpy(tmp, row, l*sizeof(int));
		
		for(int x = 2; x < l-2; x++) {
			for(p = 0; p < cntP; p++)
				if(row[x-2] == pat[p].a && row[x-1] == pat[p].b && row[x] == pat[p].c && row[x+1] == pat[p].d && row[x+2] == pat[p].e)
					break;
			tmp[x] = p < cntP ? 1 : 0;
		}
		
		memcpy(row, tmp, l*sizeof(int));

		p = 0;
		for(int j = 0; j < l; j++) 
			p += row[j] ? (j - iLen) : 0;

		if(p - oldSum == lastDiff)
			period++;
		else {
			period = 0;
			lastDiff = p - oldSum;
			sum = p;
		}
		oldSum = p;
	}

	printf("12b: %llu\n\n", (unsigned long long)(50000000000 - i + period) * lastDiff + sum);

	free(input);
	input = NULL;
	free(pat);
	pat = NULL;
}