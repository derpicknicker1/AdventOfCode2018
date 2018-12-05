/*
--- Day 4: Repose Record ---
You've sneaked into another supply closet - this time, it's across from the prototype suit manufacturing lab. You need to sneak inside and fix the issues with the suit, but there's a guard stationed outside the lab, so this is as close as you can safely get.

As you search the closet for anything that might help, you discover that you're not the first person to want to sneak in. Covering the walls, someone has spent an hour starting every midnight for the past few months secretly observing this guard post! They've been writing down the ID of the one guard on duty that night - the Elves seem to have decided that one guard was enough for the overnight shift - as well as when they fall asleep or wake up while at their post (your puzzle input).

For example, consider the following records, which have already been organized into chronological order:

[1518-11-01 00:00] Guard #10 begins shift
[1518-11-01 00:05] falls asleep
[1518-11-01 00:25] wakes up
[1518-11-01 00:30] falls asleep
[1518-11-01 00:55] wakes up
[1518-11-01 23:58] Guard #99 begins shift
[1518-11-02 00:40] falls asleep
[1518-11-02 00:50] wakes up
[1518-11-03 00:05] Guard #10 begins shift
[1518-11-03 00:24] falls asleep
[1518-11-03 00:29] wakes up
[1518-11-04 00:02] Guard #99 begins shift
[1518-11-04 00:36] falls asleep
[1518-11-04 00:46] wakes up
[1518-11-05 00:03] Guard #99 begins shift
[1518-11-05 00:45] falls asleep
[1518-11-05 00:55] wakes up
Timestamps are written using year-month-day hour:minute format. The guard falling asleep or waking up is always the one whose shift most recently started. Because all asleep/awake times are during the midnight hour (00:00 - 00:59), only the minute portion (00 - 59) is relevant for those events.

Visually, these records show that the guards are asleep at these times:

Date   ID   Minute
            000000000011111111112222222222333333333344444444445555555555
            012345678901234567890123456789012345678901234567890123456789
11-01  #10  .....####################.....#########################.....
11-02  #99  ........................................##########..........
11-03  #10  ........................#####...............................
11-04  #99  ....................................##########..............
11-05  #99  .............................................##########.....
The columns are Date, which shows the month-day portion of the relevant day; ID, which shows the guard on duty that day; and Minute, which shows the minutes during which the guard was asleep within the midnight hour. (The Minute column's header shows the minute's ten's digit in the first row and the one's digit in the second row.) Awake is shown as ., and asleep is shown as #.

Note that guards count as asleep on the minute they fall asleep, and they count as awake on the minute they wake up. For example, because Guard #10 wakes up at 00:25 on 1518-11-01, minute 25 is marked as awake.

If you can figure out the guard most likely to be asleep at a specific time, you might be able to trick that guard into working tonight so you can have the best chance of sneaking in. You have two strategies for choosing the best guard/minute combination.

Strategy 1: Find the guard that has the most minutes asleep. What minute does that guard spend asleep the most?

In the example above, Guard #10 spent the most minutes asleep, a total of 50 minutes (20+25+5), while Guard #99 only slept for a total of 30 minutes (10+10+10). Guard #10 was asleep most during minute 24 (on two days, whereas any other minute the guard was asleep was only seen on one day).

While this example listed the entries in chronological order, your entries are in the order you found them. You'll need to organize them before they can be analyzed.

What is the ID of the guard you chose multiplied by the minute you chose? (In the above example, the answer would be 10 * 24 = 240.)

Your puzzle answer was 101262.

--- Part Two ---
Strategy 2: Of all guards, which guard is most frequently asleep on the same minute?

In the example above, Guard #99 spent minute 45 asleep more than any other guard or minute - three times in total. (In all other cases, any guard spent any minute asleep at most twice.)

What is the ID of the guard you chose multiplied by the minute you chose? (In the above example, the answer would be 99 * 45 = 4455.)

Your puzzle answer was 71976.
*/

#include "advent.h"

typedef struct Log {
	int id, min, gid, mode;
} Log;

static Log *logs;
static int cntL = 0;
static int cntG = 0;

/*##########################
# Get input data from file #
##########################*/
static int getInput(char *f) {
	char * line = NULL;
	size_t l = 0;
	cntL = 0;
	cntG = 0;

	FILE *file=fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}
	
	while( getline(&line, &l, file) != -1 ) {
		int M, d, h, m, g = 0;
		char l[10];

		if(strchr(line,'#'))
			sscanf(line, "[%*d-%d-%d %d:%d] %s #%d", &M,&d,&h,&m,&l,&g);
		else
			sscanf(line, "[%*d-%d-%d %d:%d] %s", &M,&d,&h,&m,&l);

		logs = realloc(logs, ++cntL * sizeof(Log));
		
		logs[cntL-1].id = m + h*100 + d*10000 + M*1000000;
		logs[cntL-1].min = m;
		logs[cntL-1].gid = g;
		logs[cntL-1].mode = l[0];

		if(g > cntG)
			cntG = g;
	}

	cntG++;
	free(line);
	fclose(file);
	return 1;
}


static void swap(Log* a, Log* b) {
	Log t = *a;
	*a = *b;
	*b = t;
} 


static void qSort(Log *arr, int low, int high) {
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


static int solve(char *f, int choose) {

	if(!getInput(f))
		return 0;

	int guards[cntG][61];
	int gID = 0, ret = 0, minMax = 0, day = 0;

	memset(guards, 0, sizeof(guards) );

	qSort(logs, 0, cntL - 1);

	for(int i = 0; i < cntL; i++) {
		if(logs[i].gid != 0)
			gID = logs[i].gid;
		else {
			if(logs[i].mode == 'f')
				minMax = logs[i].min;
		 	else if(logs[i].mode == 'w') {
		 		for(int j = minMax; j < logs[i].min; j++) {
		 			guards[gID][j]++;
					guards[gID][60]++;
		 		}
		 	}
		}
	}
	free(logs);
	logs = NULL;

	if(choose) { // solve B

		gID = 0;
		minMax = 0;

		for(int i = 0; i < cntG; i++)
			for(int j = 0; j < 60; j++)
				if(guards[i][j] > minMax) {
					minMax = guards[i][j];
					ret = i * j;
				}
	}

	else { // solve A

		gID = 0;
		minMax = 0;

		for(int i = 0; i < cntG; i++)
			if(guards[i][60] > minMax) {
				gID = i;
				minMax = guards[i][60];
			}

		minMax = 0;

		for(int i = 0; i < 60; i++)
			if(guards[gID][i] > minMax){
				minMax = guards[gID][i];
				ret = i * gID;
			}	
	}	

	return ret;
}


/*##########################
# Function to solve part A #
##########################*/
void get4a(char * f) {

	printf("4a: %d\n", solve(f, 0));

}


/*##########################
# Function to solve part B #
##########################*/
void get4b(char *f) {

	printf("4b: %d\n\n", solve(f, 1));

}