#include "stdio.h"

#define SIZE 1000000	// Number of intergers

void sort(char *file_in, char *file_out, long size);
int long_compare(void const *a, void const *b);

int main()
{
	sort("input.txt", "output.txt", SIZE);
	return 0;
}

void sort(char *file_in, char *file_out, long size)
{
	long t = size / 2, tmp;
	long *arr = (long*)malloc((t + 1) * sizeof(long));

	FILE *fin = fopen(file_in, "r");
	FILE *fout = fopen(file_out, "w");

	// Read data from file by 2 times
	for(char times = 0; times < 2; times++){
		// Input the half of file data to array 'arr'
		for(long i = 0; i < t; i++){
			fscanf(fin, "%ld", &tmp);
			arr[i] = tmp;
		}
		// Sort array 'arr' by 'quick sort'
		qsort(arr, t, sizeof(long), long_compare);
		for(long i = 0; i < t; i++)
			fprintf(fout, "%ld ", arr[i]);

		t = size - t;
	}

	free(arr);
	fclose(fin);
	fclose(fout);
}

int long_compare(void const *a, void const *b)
{
	return *(long*)a - *(long*)b;
}