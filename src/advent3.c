/*
--- Day 3: No Matter How You Slice It ---
The Elves managed to locate the chimney-squeeze prototype fabric for Santa's suit (thanks to someone who helpfully wrote its box IDs on the wall of the warehouse in the middle of the night). Unfortunately, anomalies are still affecting them - nobody can even agree on how to cut the fabric.

The whole piece of fabric they're working on is a very large square - at least 1000 inches on each side.

Each Elf has made a claim about which area of fabric would be ideal for Santa's suit. All claims have an ID and consist of a single rectangle with edges parallel to the edges of the fabric. Each claim's rectangle is defined as follows:

The number of inches between the left edge of the fabric and the left edge of the rectangle.
The number of inches between the top edge of the fabric and the top edge of the rectangle.
The width of the rectangle in inches.
The height of the rectangle in inches.
A claim like #123 @ 3,2: 5x4 means that claim ID 123 specifies a rectangle 3 inches from the left edge, 2 inches from the top edge, 5 inches wide, and 4 inches tall. Visually, it claims the square inches of fabric represented by # (and ignores the square inches of fabric represented by .) in the diagram below:

...........
...........
...#####...
...#####...
...#####...
...#####...
...........
...........
...........
The problem is that many of the claims overlap, causing two or more claims to cover part of the same areas. For example, consider the following claims:

#1 @ 1,3: 4x4
#2 @ 3,1: 4x4
#3 @ 5,5: 2x2
Visually, these claim the following areas:

........
...2222.
...2222.
.11XX22.
.11XX22.
.111133.
.111133.
........
The four square inches marked with X are claimed by both 1 and 2. (Claim 3, while adjacent to the others, does not overlap either of them.)

If the Elves all proceed with their own plans, none of them will have enough fabric. How many square inches of fabric are within two or more claims?

Your puzzle answer was 105071.

--- Part Two ---
Amidst the chaos, you notice that exactly one claim doesn't overlap by even a single square inch of fabric with any other claim. If you can somehow draw attention to it, maybe the Elves will be able to make Santa's suit after all!

For example, in the claims above, only claim 3 is intact after all claims are made.

What is the ID of the only claim that doesn't overlap?

Your puzzle answer was 222.
*/

#include "advent.h"

static char map[1000][1000] = {};
static int **claims;
static int cntC = 0;

static void cleanup() {
	cntC = 0;

    for(int y = 0; y < 1000; y++)
		for(int x = 0; x < 1000; x++)
			map[y][x] = 0;

	for(int i = 0; i < cntC; i++)
		free(claims[i]);
	free(claims);
	claims = NULL;
}

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
	
	while( getline(&line, &l, file) != -1 ) {
		int left, top, width, height;
		sscanf(line, "#%*d @ %d,%d: %dx%d",  &left, &top, &width, &height);
		for(int y = 0; y < height; y++)
			for(int x = 0; x < width; x++)
				map[top+y][left+x]++;
		claims = (int**)realloc(claims, ++cntC * sizeof(int*));
		claims[cntC-1] = (int*)malloc(4 * sizeof(int));
		int tmp[4] = {left, top,width, height};
		memcpy(claims[cntC-1], tmp, 4 * sizeof(int));
	}

	free(line);
	fclose(file);
	return 1;
}


/*##########################
# Function to solve part A #
##########################*/
void get3a(char * f) {

	if(!getInput(f))
		return;

	int cnt = 0;

	for(int y = 0; y < 1000; y++)
		for(int x = 0; x < 1000; x++)
			if(map[y][x] > 1)
				cnt++;

	printf("3a: %d\n", cnt);

	cleanup();
}


/*##########################
# Function to solve part B #
##########################*/
void get3b(char *f) {

	if(!getInput(f))
		return;

	int found = 0, id;

	for(id = 0; id < cntC && !found && (found = 1); id++)
		for(int y = 0; y < claims[id][3] && found; y++)
			for(int x = 0; x < claims[id][2]; x++)
				if(map[claims[id][1] + y][claims[id][0] + x] > 1){
					found = 0;
					break;
				}

	printf("3b: %d\n\n", id);

	cleanup();
}