#include "advent.h"

#define execute(s) 	printf("Solving %d...\n", s); 	\
					fflush(stdout); 				\
					get##s##a("input/" #s ".txt"); 	\
					get##s##b("input/" #s ".txt");	\
					getTime(s);

clock_t begin;

void getTime(int i) {
	double timeSpent = (double)(clock() - begin) / CLOCKS_PER_SEC;
	begin = clock();
	printf("Runtime %d: %.3f\n\n\n", i, timeSpent);
}					

int main() {
	
	printf("\n\n#################\n### Solutions ###\n#################\n\n");

	clock_t beginAll = clock();
	begin = clock();

	//execute(0) // EXAMPLE
	execute(1)
	execute(2)
	execute(3)
	execute(4)
	execute(5)
	execute(6)
	execute(7)
	execute(8)
	execute(9)
	/* execute(10)
	execute(11)
	execute(12)
	execute(13)
	execute(14)
	execute(15)
	execute(16)
	execute(17)
	execute(18)
	execute(19)
	execute(20)
	execute(21)
	execute(22)
	execute(23)
	execute(24)
	execute(25)
	*/
	double timeSpent = (double)(clock() - beginAll) / CLOCKS_PER_SEC;
	printf("Overall Runtime: %.3f\n\n", timeSpent);
	system("Pause");

	return 1;
}