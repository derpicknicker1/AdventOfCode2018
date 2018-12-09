/*
--- Day 9: Marble Mania ---
You talk to the Elves while you wait for your navigation system to initialize. To pass the time, they introduce you to their favorite marble game.

The Elves play this game by taking turns arranging the marbles in a circle according to very particular rules. The marbles are numbered starting with 0 and increasing by 1 until every marble has a number.

First, the marble numbered 0 is placed in the circle. At this point, while it contains only a single marble, it is still a circle: the marble is both clockwise from itself and counter-clockwise from itself. This marble is designated the current marble.

Then, each Elf takes a turn placing the lowest-numbered remaining marble into the circle between the marbles that are 1 and 2 marbles clockwise of the current marble. (When the circle is large enough, this means that there is one marble between the marble that was just placed and the current marble.) The marble that was just placed then becomes the current marble.

However, if the marble that is about to be placed has a number which is a multiple of 23, something entirely different happens. First, the current player keeps the marble they would have placed, adding it to their score. In addition, the marble 7 marbles counter-clockwise from the current marble is removed from the circle and also added to the current player's score. The marble located immediately clockwise of the marble that was removed becomes the new current marble.

For example, suppose there are 9 players. After the marble with value 0 is placed in the middle, each player (shown in square brackets) takes a turn. The result of each of those turns would produce circles of marbles like this, where clockwise is to the right and the resulting current marble is in parentheses:

[-] (0)
[1]  0 (1)
[2]  0 (2) 1 
[3]  0  2  1 (3)
[4]  0 (4) 2  1  3 
[5]  0  4  2 (5) 1  3 
[6]  0  4  2  5  1 (6) 3 
[7]  0  4  2  5  1  6  3 (7)
[8]  0 (8) 4  2  5  1  6  3  7 
[9]  0  8  4 (9) 2  5  1  6  3  7 
[1]  0  8  4  9  2(10) 5  1  6  3  7 
[2]  0  8  4  9  2 10  5(11) 1  6  3  7 
[3]  0  8  4  9  2 10  5 11  1(12) 6  3  7 
[4]  0  8  4  9  2 10  5 11  1 12  6(13) 3  7 
[5]  0  8  4  9  2 10  5 11  1 12  6 13  3(14) 7 
[6]  0  8  4  9  2 10  5 11  1 12  6 13  3 14  7(15)
[7]  0(16) 8  4  9  2 10  5 11  1 12  6 13  3 14  7 15 
[8]  0 16  8(17) 4  9  2 10  5 11  1 12  6 13  3 14  7 15 
[9]  0 16  8 17  4(18) 9  2 10  5 11  1 12  6 13  3 14  7 15 
[1]  0 16  8 17  4 18  9(19) 2 10  5 11  1 12  6 13  3 14  7 15 
[2]  0 16  8 17  4 18  9 19  2(20)10  5 11  1 12  6 13  3 14  7 15 
[3]  0 16  8 17  4 18  9 19  2 20 10(21) 5 11  1 12  6 13  3 14  7 15 
[4]  0 16  8 17  4 18  9 19  2 20 10 21  5(22)11  1 12  6 13  3 14  7 15 
[5]  0 16  8 17  4 18(19) 2 20 10 21  5 22 11  1 12  6 13  3 14  7 15 
[6]  0 16  8 17  4 18 19  2(24)20 10 21  5 22 11  1 12  6 13  3 14  7 15 
[7]  0 16  8 17  4 18 19  2 24 20(25)10 21  5 22 11  1 12  6 13  3 14  7 15
The goal is to be the player with the highest score after the last marble is used up. Assuming the example above ends after the marble numbered 25, the winning score is 23+9=32 (because player 5 kept marble 23 and removed marble 9, while no other player got any points in this very short example game).

Here are a few more examples:

10 players; last marble is worth 1618 points: high score is 8317
13 players; last marble is worth 7999 points: high score is 146373
17 players; last marble is worth 1104 points: high score is 2764
21 players; last marble is worth 6111 points: high score is 54718
30 players; last marble is worth 5807 points: high score is 37305
What is the winning Elf's score?

Your puzzle answer was 405143.

--- Part Two ---
Amused by the speed of your answer, the Elves are curious:

What would the new winning Elf's score be if the number of the last marble were 100 times larger?

Your puzzle answer was 3411514667.
*/

#include "advent.h"

typedef struct Marble {
	int val;
	struct Marble *next, *prev;
} Marble;

static int numP, maxVal;

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
		sscanf(line, "%d players; last marble is worth %d points", &numP, &maxVal);
	else 
		return 0;

	free(line);
	fclose(file);
	return 1;
}


static unsigned int solve(char *f, int mul) {
	if(!getInput(f))
		return 0;

	maxVal *= mul;

	unsigned int pScore[numP], player = 0, max = 0;
	memset(pScore, 0, sizeof(pScore));

	Marble *head = malloc(sizeof(Marble));
	head->val = 0;
	head->next = head;
	head->prev = head;

	for(int i = 1; i <= maxVal; i++) {

		if(i % 23 == 0){

			for(int j = 0; j < 7; j++)
				head = head->prev;

			pScore[player] += head->val + i;

			Marble *tmp = head;
			head->prev->next = head->next;
			head = head->next;
			free(tmp);

			if(pScore[player] > max)
				max = pScore[player];
		}

		else{
			head = head->next;
			Marble *newMarble = malloc(sizeof(Marble));
			newMarble->val = i;
			newMarble->next = head->next;
			newMarble->prev = head;
			head->next = newMarble;
			head = newMarble;
			head->next->prev = newMarble;
		}

		if(++player == numP)
			player = 0;
	}

	while(head != head->next) {
		Marble *tmp   = head->next;
		head->next = head->next->next;
		free(tmp);
	}
	free(head);

	return max;
}

/*##########################
# Function to solve part A #
##########################*/
void get9a(char * f) {

	printf("9a: %u\n", solve(f, 1));

}


/*##########################
# Function to solve part B #
##########################*/
void get9b(char *f) {
	
	printf("9b: %u\n\n", solve(f, 100));

}