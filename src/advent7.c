/*
--- Day 7: The Sum of Its Parts ---
You find yourself standing on a snow-covered coastline; apparently, you landed a little off course. The region is too hilly to see the North Pole from here, but you do spot some Elves that seem to be trying to unpack something that washed ashore. It's quite cold out, so you decide to risk creating a paradox by asking them for directions.

"Oh, are you the search party?" Somehow, you can understand whatever Elves from the year 1018 speak; you assume it's Ancient Nordic Elvish. Could the device on your wrist also be a translator? "Those clothes don't look very warm; take this." They hand you a heavy coat.

"We do need to find our way back to the North Pole, but we have higher priorities at the moment. You see, believe it or not, this box contains something that will solve all of Santa's transportation problems - at least, that's what it looks like from the pictures in the instructions." It doesn't seem like they can read whatever language it's in, but you can: "Sleigh kit. Some assembly required."

"'Sleigh'? What a wonderful name! You must help us assemble this 'sleigh' at once!" They start excitedly pulling more parts out of the box.

The instructions specify a series of steps and requirements about which steps must be finished before others can begin (your puzzle input). Each step is designated by a single letter. For example, suppose you have the following instructions:

Step C must be finished before step A can begin.
Step C must be finished before step F can begin.
Step A must be finished before step B can begin.
Step A must be finished before step D can begin.
Step B must be finished before step E can begin.
Step D must be finished before step E can begin.
Step F must be finished before step E can begin.
Visually, these requirements look like this:


  -->A--->B--
 /    \      \
C      -->D----->E
 \           /
  ---->F-----
Your first goal is to determine the order in which the steps should be completed. If more than one step is ready, choose the step which is first alphabetically. In this example, the steps would be completed as follows:

Only C is available, and so it is done first.
Next, both A and F are available. A is first alphabetically, so it is done next.
Then, even though F was available earlier, steps B and D are now also available, and B is the first alphabetically of the three.
After that, only D and F are available. E is not available because only some of its prerequisites are complete. Therefore, D is completed next.
F is the only choice, so it is done next.
Finally, E is completed.
So, in this example, the correct order is CABDFE.

In what order should the steps in your instructions be completed?

Your puzzle answer was PFKQWJSVUXEMNIHGTYDOZACRLB.

--- Part Two ---
As you're about to begin construction, four of the Elves offer to help. "The sun will set soon; it'll go faster if we work together." Now, you need to account for multiple people working on steps simultaneously. If multiple steps are available, workers should still begin them in alphabetical order.

Each step takes 60 seconds plus an amount corresponding to its letter: A=1, B=2, C=3, and so on. So, step A takes 60+1=61 seconds, while step Z takes 60+26=86 seconds. No time is required between steps.

To simplify things for the example, however, suppose you only have help from one Elf (a total of two workers) and that each step takes 60 fewer seconds (so that step A takes 1 second and step Z takes 26 seconds). Then, using the same instructions as above, this is how each second would be spent:

Second   Worker 1   Worker 2   Done
   0        C          .        
   1        C          .        
   2        C          .        
   3        A          F       C
   4        B          F       CA
   5        B          F       CA
   6        D          F       CAB
   7        D          F       CAB
   8        D          F       CAB
   9        D          .       CABF
  10        E          .       CABFD
  11        E          .       CABFD
  12        E          .       CABFD
  13        E          .       CABFD
  14        E          .       CABFD
  15        .          .       CABFDE
Each row represents one second of time. The Second column identifies how many seconds have passed as of the beginning of that second. Each worker column shows the step that worker is currently doing (or . if they are idle). The Done column shows completed steps.

Note that the order of the steps has changed; this is because steps now take time to finish and multiple workers can begin multiple steps simultaneously.

In this example, it would take 15 seconds for two workers to complete these steps.

With 5 workers and the 60+ second step durations described above, how long will it take to complete all of the steps?

Your puzzle answer was 864.
*/

#include "advent.h"

typedef struct {
	int first, second;
} Arc;


static int cnt, workers[5][3] = {}, order = 26, *vertices = NULL, *arcs = NULL;
static Arc *input = NULL;
 
static int is_root(int v) {
	int root = 1;
	for (int a = 0; a < cnt && root; a++) {
		root = !arcs[a] || input[a].second != v;
	}
	return root;
}
 
static int get_roots() {
	int vSize = 0;
	for (int v = 0; v < order; v++)
		if (is_root(v)) {
			vertices[v] = 1;
			vSize++;
		}
	return vSize;
}

static int getWorker() {
	for(int i = 0; i < 5; i++)
		if(workers[i][0] == 0)
			return i;
	return -1;
}

static void doWork() {
	for(int i = 0; i < 5; i++)
		if(workers[i][0] > 0)
			if(--workers[i][0] == 0)
				workers[i][2] = 1;
}

static int allDone() {
	for(int i = 0; i < 5; i++)
		if(workers[i][0] != 0)
			return 0;
	return 1;
}

static void topo_sort(int *sec, char **sorted) {
	*sorted = malloc((order+1) * sizeof(char));
	vertices = calloc(order, sizeof(int));
	arcs = malloc(cnt * sizeof(int));
	int v = 0, vSize, sorted_size = 0;

	for (int i = 0; i < cnt; i++)
		arcs[i] = 1;

	vSize = get_roots();

	while (vSize > 0 || !allDone()) {

		while(v != order) {
			int w = getWorker();

			for (v = 0; v < order && vertices[v] != 1; v++);
			
			if(w > -1 && v != order){
				workers[w][0] = v + 61;
				workers[w][1] = v;
				workers[w][2] = 0;
				vertices[v] = 0;
			}
		}
		
		doWork();

		for(int j = 0; j < 5; j++){
			if(workers[j][2] == 1) {
				workers[j][2] = 0;
				v = workers[j][1];
				vSize--;
				(*sorted)[sorted_size++] = v + 65;
				for (int i = 0; i < cnt; i++) {
					if (arcs[i] && input[i].first == v) {
						arcs[i] = 0;
						if (is_root(input[i].second)) {
							vertices[input[i].second] = 1;
							vSize++;
						} 
					}
				}
			}
		}
		(*sec)++;
	}
	(*sorted)[sorted_size] = '\0';
	free(vertices);
	free(arcs);
}

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
		char a, b;
		sscanf(line, "Step %c must be finished before step %c can begin.", &a, &b);
		input = realloc(input, ++cnt * sizeof(Arc));
		input[cnt - 1].first = a - 65;
		input[cnt - 1].second = b - 65;
	}

	free(line);
	fclose(file);
	return 1;
}


/*##########################
# Function to solve part A #
##########################*/
void get7a(char * f) {

	if(!getInput(f))
		return;

	int time = 0;
	char *sorted;

	topo_sort(&time, &sorted);	

	printf("7a: %s\n", sorted);
	printf("7b: %d\n\n", time);
	
	free(sorted);
	free(input);
	input = NULL;
}


/*##########################
# Function to solve part B #
##########################*/
void get7b(char *f) {
	//see get7a();
	return;
}