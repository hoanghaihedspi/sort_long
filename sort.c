#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void sort(char *file_in, char *file_out);
void merge_file(char *file_tmp0, long size0, char *file_tmp1, long size1, char *file_out);
void merge(char *file_tmp, long size_file, long arr[], long size_arr, char *file_out);
void remove_file(char *file_name);
int long_compare(const void *a, const void *b);

int main()
{
	sort("input.txt", "output.txt");
	return 0;
}

void sort(char *file_in, char *file_out)
{
	char *file_tmp0 = "tmp0~.txt", *file_tmp1 = "tmp1~.txt";
	FILE *fin = fopen(file_in, "r");
	FILE *ftmp[2];
	ftmp[0] = fopen(file_tmp0, "w");
	ftmp[1] = fopen(file_tmp1, "w");
	if(!fin || !ftmp[0] || !ftmp[1]){ printf("Error open file!\n"); exit(1); }

	long size;
	fscanf(fin, "%ld", &size);

	long size_file = size / 3, tmp;
	long *arr = (long*)malloc(size_file * sizeof(long));
	
	for(int times = 0; times < 2; times++){
		// Input the 1/3 of file data to array 'arr'
		for(long i = 0; i < size_file; i++){
			fscanf(fin, "%ld", &tmp);
			arr[i] = tmp;
		}
		// Sort array 'arr' and write to file.
		qsort(arr, size_file, sizeof(long), long_compare);
		for(long i = 0; i < size_file; i++)
			fprintf(ftmp[times], "%ld ", arr[i]);
		fclose(ftmp[times]);
	}
	free(arr);

	// Input the other 1/3 of file data to array 'arr'
	long size_arr = size - 2 * size_file;
	arr = (long)malloc(size_arr * sizeof(long));
	for(long i = 0; i < size_arr; i++){
		fscanf(fin, "%ld", &tmp);
		arr[i] = tmp;
	}
	// Sort array 'arr'
	qsort(arr, size_arr, sizeof(long), long_compare);

	fclose(fin);

	char *file_tmp = "tmp~.txt";
	merge_file(file_tmp0, size_file, file_tmp1, size_file, file_tmp);
	merge(file_tmp, size - size_arr, arr, size_arr, file_out);
	free(arr);
}

void merge_file(char *file_tmp0, long size0, char *file_tmp1, long size1, char *file_out)
{
	FILE *f = fopen(file_out, "w");
	FILE *f1 = fopen(file_tmp0, "r");
	FILE *f2 = fopen(file_tmp1, "r");
	if(!f || !f1 || !f2){ printf("Error open file!\n"); exit(1); }

	long tmp1, tmp2;

	fscanf(f1, "%ld", &tmp1);
	fscanf(f2, "%ld", &tmp2);
	while(size0 > 0 && size1 > 0){
		if(tmp1 < tmp2){
			fprintf(f, "%ld ", tmp1);
			fscanf(f1, "%ld", &tmp1);
			size0--;
		}
		else{
			fprintf(f, "%ld ", tmp2);
			fscanf(f2, "%ld", &tmp2);
			size1--;
		}
	}
	while(size0-- > 0){
		fprintf(f, "%ld ", tmp1);
		fscanf(f1, "%ld", &tmp1);
	}
	while(size1-- > 0){
		fprintf(f, "%ld ", tmp2);
		fscanf(f2, "%ld", &tmp2);
	}
	
	fclose(f); fclose(f1); fclose(f2);
	remove_file(file_tmp0);
	remove_file(file_tmp1);
}

void merge(char *file_tmp, long size_file, long arr[], long size_arr, char *file_out)
{
	FILE *fout = fopen(file_out, "w");
	FILE *ftmp = fopen(file_tmp, "r");
	if(!fout || !ftmp){ printf("Error open file!\n"); exit(1); }

	fprintf(fout, "%ld\n", size_file + size_arr);

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