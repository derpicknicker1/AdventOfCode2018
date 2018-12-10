/*
--- Day 10: The Stars Align ---
It's no use; your navigation system simply isn't capable of providing walking directions in the arctic circle, and certainly not in 1018.

The Elves suggest an alternative. In times like these, North Pole rescue operations will arrange points of light in the sky to guide missing Elves back to base. Unfortunately, the message is easy to miss: the points move slowly enough that it takes hours to align them, but have so much momentum that they only stay aligned for a second. If you blink at the wrong time, it might be hours before another message appears.

You can see these points of light floating in the distance, and record their position in the sky and their velocity, the relative change in position per second (your puzzle input). The coordinates are all given from your perspective; given enough time, those positions and velocities will move the points into a cohesive message!

Rather than wait, you decide to fast-forward the process and calculate what the points will eventually spell.

For example, suppose you note the following points:

position=< 9,  1> velocity=< 0,  2>
position=< 7,  0> velocity=<-1,  0>
position=< 3, -2> velocity=<-1,  1>
position=< 6, 10> velocity=<-2, -1>
position=< 2, -4> velocity=< 2,  2>
position=<-6, 10> velocity=< 2, -2>
position=< 1,  8> velocity=< 1, -1>
position=< 1,  7> velocity=< 1,  0>
position=<-3, 11> velocity=< 1, -2>
position=< 7,  6> velocity=<-1, -1>
position=<-2,  3> velocity=< 1,  0>
position=<-4,  3> velocity=< 2,  0>
position=<10, -3> velocity=<-1,  1>
position=< 5, 11> velocity=< 1, -2>
position=< 4,  7> velocity=< 0, -1>
position=< 8, -2> velocity=< 0,  1>
position=<15,  0> velocity=<-2,  0>
position=< 1,  6> velocity=< 1,  0>
position=< 8,  9> velocity=< 0, -1>
position=< 3,  3> velocity=<-1,  1>
position=< 0,  5> velocity=< 0, -1>
position=<-2,  2> velocity=< 2,  0>
position=< 5, -2> velocity=< 1,  2>
position=< 1,  4> velocity=< 2,  1>
position=<-2,  7> velocity=< 2, -2>
position=< 3,  6> velocity=<-1, -1>
position=< 5,  0> velocity=< 1,  0>
position=<-6,  0> velocity=< 2,  0>
position=< 5,  9> velocity=< 1, -2>
position=<14,  7> velocity=<-2,  0>
position=<-3,  6> velocity=< 2, -1>
Each line represents one point. Positions are given as <X, Y> pairs: X represents how far left (negative) or right (positive) the point appears, while Y represents how far up (negative) or down (positive) the point appears.

At 0 seconds, each point has the position given. Each second, each point's velocity is added to its position. So, a point with velocity <1, -2> is moving to the right, but is moving upward twice as quickly. If this point's initial position were <3, 9>, after 3 seconds, its position would become <6, 3>.

Over time, the points listed above would move like this:

Initially:
........#.............
................#.....
.........#.#..#.......
......................
#..........#.#.......#
...............#......
....#.................
..#.#....#............
.......#..............
......#...............
...#...#.#...#........
....#..#..#.........#.
.......#..............
...........#..#.......
#...........#.........
...#.......#..........

After 1 second:
......................
......................
..........#....#......
........#.....#.......
..#.........#......#..
......................
......#...............
....##.........#......
......#.#.............
.....##.##..#.........
........#.#...........
........#...#.....#...
..#...........#.......
....#.....#.#.........
......................
......................

After 2 seconds:
......................
......................
......................
..............#.......
....#..#...####..#....
......................
........#....#........
......#.#.............
.......#...#..........
.......#..#..#.#......
....#....#.#..........
.....#...#...##.#.....
........#.............
......................
......................
......................

After 3 seconds:
......................
......................
......................
......................
......#...#..###......
......#...#...#.......
......#...#...#.......
......#####...#.......
......#...#...#.......
......#...#...#.......
......#...#...#.......
......#...#..###......
......................
......................
......................
......................

After 4 seconds:
......................
......................
......................
............#.........
........##...#.#......
......#.....#..#......
.....#..##.##.#.......
.......##.#....#......
...........#....#.....
..............#.......
....#......#...#......
.....#.....##.........
...............#......
...............#......
......................
......................
After 3 seconds, the message appeared briefly: HI. Of course, your message will be much longer and will take many more seconds to appear.

What message will eventually appear in the sky?

Your puzzle answer was ZNNRZJXP.

--- Part Two ---
Good thing you didn't have to wait, because that would have taken a long time - much longer than the 3 seconds in the example above.

Impressed by your sub-hour communication capabilities, the Elves are curious: exactly how many seconds would they have needed to wait for that message to appear?

Your puzzle answer was 10418.
*/

#include "advent.h"

typedef struct Pixel {
	int p[2], v[2];
} Pixel;

static Pixel *pix = NULL;
static int cnt;


/*##########################
# Get input data from file #
##########################*/
static int getInput(char *f) {
	char * line = NULL;
    size_t l = 0;
    cnt = 0;

	FILE *file=fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}
	
	while( getline(&line, &l, file) != -1 ) {
		pix = realloc(pix, ++cnt * sizeof(Pixel));
		sscanf(line, "position=<%d, %d> velocity=<%d, %d>", &pix[cnt-1].p[0], &pix[cnt-1].p[1], &pix[cnt-1].v[0], &pix[cnt-1].v[1]);
	}

	free(line);
	fclose(file);
	return 1;
}


static int getBox(int *bounds) {

	unsigned long long box = 0xFFFFFFFFFFFF;
	int cntS = 0;

	while(1) {
		int tmpBounds[4] ={-999999999, 999999999, -999999999, 999999999};

		for(int i = 0; i < cnt; i++) {
			pix[i].p[0] += pix[i].v[0];
			pix[i].p[1] += pix[i].v[1];
			if(pix[i].p[0] > tmpBounds[0])
				tmpBounds[0] = pix[i].p[0];
			if(pix[i].p[0] < tmpBounds[1])
				tmpBounds[1] = pix[i].p[0];
			if(pix[i].p[1] > tmpBounds[2])
				tmpBounds[2] = pix[i].p[1];
			if(pix[i].p[1] < tmpBounds[3])
				tmpBounds[3] = pix[i].p[1];
		}

		unsigned long long tmp = (unsigned long long)abs(tmpBounds[0] - tmpBounds[1]) * abs(tmpBounds[2] - tmpBounds[3]);
		
		if(tmp > box)
			break;

		memcpy(bounds, tmpBounds, 4 * sizeof(int));
		box = tmp;
		cntS++;
	}

	return cntS;
}


/*##########################
# Function to solve part A #
##########################*/
void get10a(char * f) {

	if(!getInput(f))
		return;

	int bounds[4];
	getBox(bounds);

	char map[abs(bounds[2] - bounds[3]) + 1][abs(bounds[0] - bounds[1]) + 2];
	memset(map, ' ', sizeof(map));

	printf("10a:\n\n");
	
	for(int i = 0; i < cnt; i++) 
		map[pix[i].p[1] - pix[i].v[1] - bounds[3]][pix[i].p[0] - pix[i].v[0] - bounds[1]] = 0xDB;

	for(int y = 0; y <= abs(bounds[2] - bounds[3]); y++) {
		map[y][abs(bounds[0] - bounds[1]) + 1] = '\0';
		printf("%s\n",map[y]);
	}

	free(pix);
	pix = NULL;
}


/*##########################
# Function to solve part B #
##########################*/
void get10b(char *f) {

	if(!getInput(f))
		return;

	int bounds[4], i = getBox(bounds);	
	
	printf("\n10b: %d\n\n", i);

	free(pix);
	pix = NULL;
}