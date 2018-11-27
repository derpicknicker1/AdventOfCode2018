#include "advent.h"

int toI(char *s) {
	int sum = 0, min = 0;
	if(*s == '-') {
		*s++;
		min++;
	}
    while (*s && *s != '\n')
        sum = sum * 10 + (*s++ - '0');
    return min?-sum:sum;
}