#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define SIZE 1000000	// Number of intergers

void sort(char *file_in, char *file_out, long size);
void merge(char *file_name1, long size_file, long arr[], long size_arr, char *file_out);
void remove_file(char *file_name);
int long_compare(const void *a, const void *b);

int main()
{
	sort("input.txt", "output.txt", SIZE);
	return 0;
}

void sort(char *file_in, char *file_out, long size)
{
	long t = size / 2, tmp;
	long *arr = (long*)malloc((t + 10) * sizeof(long));

	char *file_tmp = "tmp~.txt";
	FILE *fin = fopen(file_in, "r");
	FILE *ftmp = fopen(file_tmp, "w");
	if(!fin || !ftmp){ printf("Error open file!\n"); exit(1); }
	
	// Input the half of file data to array 'arr'
	for(long i = 0; i < t; i++){
		fscanf(fin, "%ld", &tmp);
		arr[i] = tmp;
	}
	// Sort array 'arr' and write to file.
	qsort(arr, t, sizeof(long), long_compare);
	for(long i = 0; i < t; i++)
		fprintf(ftmp, "%ld ", arr[i]);
	fclose(ftmp);

	// Input the other half of file data to array 'arr'
	for(long i = 0; i < size - t; i++){
		fscanf(fin, "%ld", &tmp);
		arr[i] = tmp;
	}
	// Sort array 'arr'
	qsort(arr, t, sizeof(long), long_compare);

	fclose(fin);

	merge(file_tmp, t, arr, size - t, file_out);
	free(arr);
}

void merge(char *file_tmp, long size_file, long arr[], long size_arr, char *file_out)
{
	FILE *fout = fopen(file_out, "w");
	FILE *ftmp = fopen(file_tmp, "r");
	if(!fout || !ftmp){ printf("Error open file!\n"); exit(1); }

	long tmp;
	long count = 0;

	fscanf(ftmp, "%ld", &tmp);
	while(size_file > 0 && count < size_arr){
		if(tmp < arr[count]){
			fprintf(fout, "%ld ", tmp);
			fscanf(ftmp, "%ld", &tmp);
			size_file--;
		}
		else{
			fprintf(fout, "%ld ", arr[count]);
			count++;
		}
	}
	while(size_file-- > 0){
		fprintf(fout, "%ld ", tmp);
		fscanf(ftmp, "%ld", &tmp);
	}
	while(count < size_arr)
		fprintf(fout, "%ld ", arr[count++]);
	
	fclose(fout);
	fclose(ftmp);
	remove_file(file_tmp);
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