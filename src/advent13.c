/*
--- Day 13: Mine Cart Madness ---
A crop of this size requires significant logistics to transport produce, soil, fertilizer, and so on. The Elves are very busy pushing things around in carts on some kind of rudimentary system of tracks they've come up with.

Seeing as how cart-and-track systems don't appear in recorded history for another 1000 years, the Elves seem to be making this up as they go along. They haven't even figured out how to avoid collisions yet.

You map out the tracks (your puzzle input) and see where you can help.

Tracks consist of straight paths (| and -), curves (/ and \), and intersections (+). Curves connect exactly two perpendicular pieces of track; for example, this is a closed loop:

/----\
|    |
|    |
\----/
Intersections occur when two perpendicular paths cross. At an intersection, a cart is capable of turning left, turning right, or continuing straight. Here are two loops connected by two intersections:

/-----\
|     |
|  /--+--\
|  |  |  |
\--+--/  |
   |     |
   \-----/
Several carts are also on the tracks. Carts always face either up (^), down (v), left (<), or right (>). (On your initial map, the track under each cart is a straight path matching the direction the cart is facing.)

Each time a cart has the option to turn (by arriving at any intersection), it turns left the first time, goes straight the second time, turns right the third time, and then repeats those directions starting again with left the fourth time, straight the fifth time, and so on. This process is independent of the particular intersection at which the cart has arrived - that is, the cart has no per-intersection memory.

Carts all move at the same speed; they take turns moving a single step at a time. They do this based on their current location: carts on the top row move first (acting from left to right), then carts on the second row move (again from left to right), then carts on the third row, and so on. Once each cart has moved one step, the process repeats; each of these loops is called a tick.

For example, suppose there are two carts on a straight track:

|  |  |  |  |
v  |  |  |  |
|  v  v  |  |
|  |  |  v  X
|  |  ^  ^  |
^  ^  |  |  |
|  |  |  |  |
First, the top cart moves. It is facing down (v), so it moves down one square. Second, the bottom cart moves. It is facing up (^), so it moves up one square. Because all carts have moved, the first tick ends. Then, the process repeats, starting with the first cart. The first cart moves down, then the second cart moves up - right into the first cart, colliding with it! (The location of the crash is marked with an X.) This ends the second and last tick.

Here is a longer example:

/->-\        
|   |  /----\
| /-+--+-\  |
| | |  | v  |
\-+-/  \-+--/
  \------/   

/-->\        
|   |  /----\
| /-+--+-\  |
| | |  | |  |
\-+-/  \->--/
  \------/   

/---v        
|   |  /----\
| /-+--+-\  |
| | |  | |  |
\-+-/  \-+>-/
  \------/   

/---\        
|   v  /----\
| /-+--+-\  |
| | |  | |  |
\-+-/  \-+->/
  \------/   

/---\        
|   |  /----\
| /->--+-\  |
| | |  | |  |
\-+-/  \-+--^
  \------/   

/---\        
|   |  /----\
| /-+>-+-\  |
| | |  | |  ^
\-+-/  \-+--/
  \------/   

/---\        
|   |  /----\
| /-+->+-\  ^
| | |  | |  |
\-+-/  \-+--/
  \------/   

/---\        
|   |  /----<
| /-+-->-\  |
| | |  | |  |
\-+-/  \-+--/
  \------/   

/---\        
|   |  /---<\
| /-+--+>\  |
| | |  | |  |
\-+-/  \-+--/
  \------/   

/---\        
|   |  /--<-\
| /-+--+-v  |
| | |  | |  |
\-+-/  \-+--/
  \------/   

/---\        
|   |  /-<--\
| /-+--+-\  |
| | |  | v  |
\-+-/  \-+--/
  \------/   

/---\        
|   |  /<---\
| /-+--+-\  |
| | |  | |  |
\-+-/  \-<--/
  \------/   

/---\        
|   |  v----\
| /-+--+-\  |
| | |  | |  |
\-+-/  \<+--/
  \------/   

/---\        
|   |  /----\
| /-+--v-\  |
| | |  | |  |
\-+-/  ^-+--/
  \------/   

/---\        
|   |  /----\
| /-+--+-\  |
| | |  X |  |
\-+-/  \-+--/
  \------/   
After following their respective paths for a while, the carts eventually crash. To help prevent crashes, you'd like to know the location of the first crash. Locations are given in X,Y coordinates, where the furthest left column is X=0 and the furthest top row is Y=0:

           111
 0123456789012
0/---\        
1|   |  /----\
2| /-+--+-\  |
3| | |  X |  |
4\-+-/  \-+--/
5  \------/   
In this example, the location of the first crash is 7,3.

Your puzzle answer was 111,13.

--- Part Two ---
There isn't much you can do to prevent crashes in this ridiculous system. However, by predicting the crashes, the Elves know where to be in advance and instantly remove the two crashing carts the moment any crash occurs.

They can proceed like this for a while, but eventually, they're going to run out of carts. It could be useful to figure out where the last cart that hasn't crashed will end up.

For example:

/>-<\  
|   |  
| /<+-\
| | | v
\>+</ |
  |   ^
  \<->/

/---\  
|   |  
| v-+-\
| | | |
\-+-/ |
  |   |
  ^---^

/---\  
|   |  
| /-+-\
| v | |
\-+-/ |
  ^   ^
  \---/

/---\  
|   |  
| /-+-\
| | | |
\-+-/ ^
  |   |
  \---/
After four very expensive crashes, a tick ends with only one cart remaining; its final location is 6,4.

What is the location of the last cart at the end of the first tick where it is the only cart left?

Your puzzle answer was 16,73.
*/

enum {UP, DOWN, LEFT, RIGHT, STRAIGHT};

typedef struct Car {
	int x, y, dir, turn, crashed, id;
} Car;

#include "advent.h"

static char **map = NULL;
static int cntL, wL;


/*##########################
# Get input data from file #
##########################*/
static int getInput(char *f) {
	char * line = NULL;
    size_t l = 0;
    cntL = 0;

	FILE *file=fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}
	
	while( getline(&line, &l, file) != -1 ) {
		wL = strlen(line);
		map = realloc(map, ++cntL * sizeof(char*));
		map[cntL - 1] = malloc(wL + 1);
		strcpy(map[cntL - 1],line);
	}

	free(line);
	fclose(file);
	return 1;
}


static void swap(Car *a, Car *b) {
	Car t = *a;
	*a = *b;
	*b = t;
} 


static void qSort(Car *arr, int low, int high) {
	if (low < high) {
		int i = (low - 1);
		for (int j = low; j < high; j++)
			if (arr[j].id <= arr[high].id)
				swap(&arr[++i], &arr[j]);
		swap(&arr[i + 1], &arr[high]);
		qSort(arr, low, i);
		qSort(arr, i + 2, high);
	}
}


static void solve(char *f,int mode, int *res) {

	if(!getInput(f))
		return;

	Car *cars = NULL;
	int cntC = 0, noCrash = 1;

	for(int y = 0; y < cntL; y++) {
		for(int x = 0; x < wL; x++) {
			if(map[y][x] == '<' || map[y][x] == '>' || map[y][x] == 'v' || map[y][x] == '^') {
				cars = realloc(cars, ++cntC * sizeof(Car));
				cars[cntC - 1].x = x;
				cars[cntC - 1].y = y;
				char c = map[y][x];
				cars[cntC - 1].dir = c == '<' ? LEFT : (c == '>' ? RIGHT : (c == 'v' ? DOWN : UP));
				cars[cntC - 1].turn = LEFT;
				cars[cntC - 1].crashed = 0;
				char buf[10] = {};
				sprintf(buf, "%3d%3d",y,x);
				cars[cntC - 1].id = toI(buf);
				if(map[y][x] == '>' || map[y][x] == '<')
					map[y][x] = '-';
				else
					map[y][x] = '|';
			}
		}
	}
	
	int numCars = cntC;
	while(numCars > 1 && noCrash) {

		qSort(cars, 0, cntC - 1);

		for(int i = 0; i < cntC; i++) {
			
			if(!cars[i].crashed) {

				if(map[cars[i].y][cars[i].x] == '-')
					cars[i].x += cars[i].dir == RIGHT ? 1 : -1;
				else if(map[cars[i].y][cars[i].x] == '|')
					cars[i].y += cars[i].dir == DOWN ? 1 : -1;
				else if(map[cars[i].y][cars[i].x] == '/') {
					switch(cars[i].dir){
						case UP: cars[i].dir = RIGHT; cars[i].x++; break;
						case DOWN: cars[i].dir = LEFT; cars[i].x--; break;
						case RIGHT: cars[i].dir = UP; cars[i].y--; break;
						case LEFT: cars[i].dir = DOWN; cars[i].y++; break;
					}
				}
				else if(map[cars[i].y][cars[i].x] == '\\') {
					switch(cars[i].dir){
						case RIGHT: cars[i].dir = DOWN; cars[i].y++; break;
						case LEFT: cars[i].dir = UP; cars[i].y--; break;
						case DOWN: cars[i].dir = RIGHT; cars[i].x++; break;
						case UP: cars[i].dir = LEFT; cars[i].x--; break;
					}
				}
				else if(map[cars[i].y][cars[i].x] == '+') {
					if(cars[i].turn == STRAIGHT) {
						if(cars[i].dir == UP) cars[i].y--;
						else if(cars[i].dir == DOWN) cars[i].y++;
						else if(cars[i].dir == RIGHT) cars[i].x++;
						else if(cars[i].dir == LEFT) cars[i].x--;
					}
					else if(cars[i].turn == LEFT) {
						if(cars[i].dir == UP) { cars[i].x--; cars[i].dir = LEFT; }
						else if(cars[i].dir == DOWN) { cars[i].x++; cars[i].dir = RIGHT; }
						else if(cars[i].dir == RIGHT) { cars[i].y--; cars[i].dir = UP; }
						else if(cars[i].dir == LEFT) { cars[i].y++; cars[i].dir = DOWN; }
					}
					if(cars[i].turn == RIGHT) {
						if(cars[i].dir == UP) { cars[i].x++; cars[i].dir = RIGHT; }
						else if(cars[i].dir == DOWN) { cars[i].x--; cars[i].dir = LEFT; }
						else if(cars[i].dir == RIGHT) { cars[i].y++; cars[i].dir = DOWN; }
						else if(cars[i].dir == LEFT) { cars[i].y--; cars[i].dir = UP; }
					}
					
					switch(cars[i].turn) {
						case LEFT: cars[i].turn = STRAIGHT; break;
						case STRAIGHT: cars[i].turn = RIGHT; break;
						case RIGHT: cars[i].turn = LEFT; break;
					}
				}

				// Part A or Part B?
				if(mode)
					for(int j = 0; j < cntC; j++){
						if(cars[i].x == cars[j].x && cars[i].y == cars[j].y && j != i && !cars[j].crashed){
							cars[i].crashed = 1;			
							cars[j].crashed = 1;
							numCars-=2;
							break;
						}
					}
				else
					for(int j = 0; j < cntC; j++){
							if(cars[i].x == cars[j].x && cars[i].y == cars[j].y && j != i){
								noCrash = 0;
								res[0] = cars[i].x;
								res[1] = cars[i].y;
								break;

							}
						}

				char buf[10] = {};
				sprintf(buf, "%3d%3d",cars[i].y,cars[i].x);
				cars[i].id = toI(buf);
			}
		}
	}

	for(int j = 0; j < cntC && mode; j++)
		if(cars[j].crashed == 0) {
			res[0] = cars[j].x;
			res[1] = cars[j].y;
			break;
		}

	for(int y = 0; y < cntL; y++)
		free(map[y]);
	free(map);
	free(cars);
	map = NULL;
}


/*##########################
# Function to solve part A #
##########################*/
void get13a(char * f) {

	int res[2];
	solve(f, 0, res);
	printf("13a: %d,%d\n", res[0], res[1]);

}


/*##########################
# Function to solve part B #
##########################*/
void get13b(char *f) {
	
	int res[2];
	solve(f, 1, res);
	printf("13b: %d,%d\n\n", res[0], res[1]);

}