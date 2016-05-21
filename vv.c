#include "stdio.h"
#include "stdlib.h"

#define LENGTH 10000
#define MIN -2147483648

int main()
{
	FILE *fi = fopen("input.txt", "r");
	FILE *fo = fopen("output.txt", "w");

	long count = 0;
	long min = 0;
	long aft_min = 0;
	long count_min = 0;
	long tmp = 0;

	fscanf(fi, "%ld", &min);
	while(!feof(fi)){
		fscanf(fi, "%ld", &tmp);
		if(tmp < min){
			aft_min = min;
			min = tmp;
			count_min = 1;
		}
		else if(tmp == min) count_min++;
	}
	for(long i = 0; i < count_min; i++)
		fprintf(fo, "%ld ", min);

	count = count_min;
	count_min = 0;
	min = aft_min;
	aft_min = MIN;

	while(count < LENGTH){
		rewind(fi);
		while(!feof(fi)){
			fscanf(fi, "%ld", &tmp);
			if(tmp == min) count_min++;
			else if(tmp > min && (tmp < aft_min || aft_min == MIN)) aft_min = tmp;
		}

		for(long i = 0; i < count_min; i++)
			fprintf(fo, "%ld ", min);

		count += count_min;
		count_min = 0;
		min = aft_min;
		aft_min = MIN;
	}

	fclose(fi);
	fclose(fo);
	return 0;
}