#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define SIZE 1000000	// Number of intergers

void sort(char *file_in, char *file_out, long size);
void merge_file(char *file_name1, long size1, char *file_name2, long size2, char *file_out);
void remove_file(char *file_name);
int long_compare(const void *a, const void *b);

int main()
{
	sort("input.txt", "output.txt", SIZE);
	// merge_file("1.txt", 3, "2.txt", 3, "output.txt");
	return 0;
}

void sort(char *file_in, char *file_out, long size)
{
	long t = size / 2, tmp;
	long *arr = (long*)malloc((t + 10) * sizeof(long));

	char *ftmp0 = "tmp0~.txt", *ftmp1 = "tmp1~.txt";
	FILE *fin = fopen(file_in, "r");
	FILE *ftmp[2];
	ftmp[0] = fopen(ftmp0, "w");
	ftmp[1] = fopen(ftmp1, "w");

	// Read data from file by 2 times
	for(int times = 0; times < 2; times++){
		// Input the half of file data to array 'arr'
		for(long i = 0; i < t; i++){
			fscanf(fin, "%ld", &tmp);
			arr[i] = tmp;
		}
		// Sort array 'arr' by 'quick sort'
		qsort(arr, t, sizeof(long), long_compare);
		for(long i = 0; i < t; i++)
			fprintf(ftmp[times], "%ld ", arr[i]);

		t = size - t;
	}

	free(arr);
	fclose(fin);
	fclose(ftmp[0]);
	fclose(ftmp[1]);

	merge_file(ftmp0, t, ftmp1, size - t, file_out);
}

void merge_file(char *file_name1, long size1, char *file_name2, long size2, char *file_out)
{
	FILE *f = fopen(file_out, "w");
	FILE *f1 = fopen(file_name1, "r");
	FILE *f2 = fopen(file_name2, "r");
	if(!f || !f1 || !f2){ printf("Error open file!\n"); exit(1); }

	long tmp1, tmp2;

	fscanf(f1, "%ld", &tmp1);
	fscanf(f2, "%ld", &tmp2);
	while(size1 > 0 && size2 > 0){
		if(tmp1 < tmp2){
			fprintf(f, "%ld ", tmp1);
			fscanf(f1, "%ld", &tmp1);
			size1--;
		}
		else{
			fprintf(f, "%ld ", tmp2);
			fscanf(f2, "%ld", &tmp2);
			size2--;
		}
	}
	while(size1-- > 0){
		fprintf(f, "%ld ", tmp1);
		fscanf(f1, "%ld", &tmp1);
	}
	while(size2-- > 0){
		fprintf(f, "%ld ", tmp2);
		fscanf(f2, "%ld", &tmp2);
	}
	
	fclose(f); fclose(f1); fclose(f2);
	remove_file(file_name1);
	remove_file(file_name2);
}

void remove_file(char *file_name)
{
	char tmp[20] = "rm ";
	strcat(tmp, file_name);
	system(tmp);
}

int long_compare(const void *a, const void *b)
{
	return (*(long*)a - *(long*)b);
}