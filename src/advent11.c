/*
--- Day 11: Chronal Charge ---
You watch the Elves and their sleigh fade into the distance as they head toward the North Pole.

Actually, you're the one fading. The falling sensation returns.

The low fuel warning light is illuminated on your wrist-mounted device. Tapping it once causes it to project a hologram of the situation: a 300x300 grid of fuel cells and their current power levels, some negative. You're not sure what negative power means in the context of time travel, but it can't be good.

Each fuel cell has a coordinate ranging from 1 to 300 in both the X (horizontal) and Y (vertical) direction. In X,Y notation, the top-left cell is 1,1, and the top-right cell is 300,1.

The interface lets you select any 3x3 square of fuel cells. To increase your chances of getting to your destination, you decide to choose the 3x3 square with the largest total power.

The power level in a given fuel cell can be found through the following process:

Find the fuel cell's rack ID, which is its X coordinate plus 10.
Begin with a power level of the rack ID times the Y coordinate.
Increase the power level by the value of the grid serial number (your puzzle input).
Set the power level to itself multiplied by the rack ID.
Keep only the hundreds digit of the power level (so 12345 becomes 3; numbers with no hundreds digit become 0).
Subtract 5 from the power level.
For example, to find the power level of the fuel cell at 3,5 in a grid with serial number 8:

The rack ID is 3 + 10 = 13.
The power level starts at 13 * 5 = 65.
Adding the serial number produces 65 + 8 = 73.
Multiplying by the rack ID produces 73 * 13 = 949.
The hundreds digit of 949 is 9.
Subtracting 5 produces 9 - 5 = 4.
So, the power level of this fuel cell is 4.

Here are some more example power levels:

Fuel cell at  122,79, grid serial number 57: power level -5.
Fuel cell at 217,196, grid serial number 39: power level  0.
Fuel cell at 101,153, grid serial number 71: power level  4.
Your goal is to find the 3x3 square which has the largest total power. The square must be entirely within the 300x300 grid. Identify this square using the X,Y coordinate of its top-left fuel cell. For example:

For grid serial number 18, the largest total 3x3 square has a top-left corner of 33,45 (with a total power of 29); these fuel cells appear in the middle of this 5x5 region:

-2  -4   4   4   4
-4   4   4   4  -5
 4   3   3   4  -4
 1   1   2   4  -3
-1   0   2  -5  -2
For grid serial number 42, the largest 3x3 square's top-left is 21,61 (with a total power of 30); they are in the middle of this region:

-3   4   2   2   2
-4   4   3   3   4
-5   3   3   4  -4
 4   3   3   4  -3
 3   3   3  -5  -1
What is the X,Y coordinate of the top-left fuel cell of the 3x3 square with the largest total power?

Your puzzle answer was 20,34.

--- Part Two ---
You discover a dial on the side of the device; it seems to let you select a square of any size, not just 3x3. Sizes from 1x1 to 300x300 are supported.

Realizing this, you now must find the square of any size with the largest total power. Identify this square by including its size as a third parameter after the top-left coordinate: a 9x9 square with a top-left corner of 3,5 is identified as 3,5,9.

For example:

For grid serial number 18, the largest total square (with a total power of 113) is 16x16 and has a top-left corner of 90,269, so its identifier is 90,269,16.
For grid serial number 42, the largest total square (with a total power of 119) is 12x12 and has a top-left corner of 232,251, so its identifier is 232,251,12.
What is the X,Y,size identifier of the square with the largest total power?

Your puzzle answer was 90,57,15.
*/

#include "advent.h"

static int gridID;


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
	
	if( getline(&line, &l, file) != -1 )
		sscanf(line, "%d", &gridID);
	else 
		return 0;

	free(line);
	fclose(file);
	return 1;
}


static int c(int x, int y) {
	return (((x+10) * y) + gridID) * (x+10) / 100 % 10 - 5;
}


/*##########################
# Function to solve part A #
##########################*/
void get11a(char * f) {

	if(!getInput(f))
		return;

	int pos[2], max = INT_MIN;

	for (int y = 1; y < 299; y++)
		for (int x = 1; x < 299; x++) {
			int sum = c(x,y) + c(x+1,y) + c(x+2,y) + c(x,y+1) + c(x+1,y+1) + c(x+2,y+1) + c(x,y+2) + c(x+1,y+2) + c(x+2,y+2);
			if (sum > max) {
				max = sum;
				pos[0] = x;
				pos[1] = y;
			}
		}

	printf("11a: %d,%d\n", pos[0], pos[1]);
}


/*##########################
# Function to solve part B #
##########################*/
void get11b(char *f) {

	if(!getInput(f))
		return;

	int pos[3], max = INT_MIN, map[301][301] = {};

	for(int y = 1; y <= 300; y++)
		for(int x = 1; x <= 300; x++)
			map[y][x] = c(x, y) + map[y - 1][x] + map[y][x - 1] - map[y - 1][x - 1];

	for(int s = 1; s <= 300; s++)
		for(int y = s; y <= 300; y++)
			for(int x = s; x <= 300; x++) {
				int sum = map[y][x] - map[y - s][x] - map[y][x - s] + map[y - s][x - s];
				if(sum > max) {
					pos[0] = x - s + 1;
					pos[1] = y - s + 1;
					pos[2] = s;
					max = sum;
				}
			}
	
	printf("11b: %d,%d,%d\n\n", pos[0], pos[1], pos[2]);
}