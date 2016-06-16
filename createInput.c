// Copyright: Hoang Van Hai

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#define LENGTH 1000000
#define RAND_MAX 2147483647

int main()
{
	FILE *f;
	f = fopen("input.txt", "w");
	fprintf(f, "%d\n", LENGTH);

	int length = 0;
	int num;
	
	srand(time(0));
	while(length++ < LENGTH){
		if(rand() % 2) num = rand();
		else num = - rand() - 1;

		fprintf(f, "%d ", num);
	}

	fclose(f);

	return 0;
}