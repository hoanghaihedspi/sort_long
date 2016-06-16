#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void sort(char *file_in, char *file_out);
void merge(char *file_name1, int size_file, int *arr, int size_arr, char *file_out);
void remove_file(char *file_name);
void adjust_heap(int arr[], int root, int n);
void heap_sort(int arr[], int n);
void swap(int *a, int *b);

int main()
{
	sort("input.txt", "output.txt");
	return 0;
}

void sort(char *file_in, char *file_out)
{
	char *file_tmp = "tmp~.txt";
	FILE *fin = fopen(file_in, "r");
	FILE *ftmp = fopen(file_tmp, "w");
	if(!fin || !ftmp){ printf("Error open file!\n"); exit(1); }

	int size;
	fscanf(fin, "%d", &size);

	int size_file = size / 2;
	int size_arr = size - size_file;

	int *arr = (int*)malloc(size_arr * sizeof(int));
	int tmp;
	
	// Input the half of file data to array 'arr'
	for(int i = 0; i < size_file; i++){
		fscanf(fin, "%d", &tmp);
		arr[i] = tmp;
	}
	// Sort array 'arr' and write to file.
	heap_sort(arr, size_file);
	for(int i = 0; i < size_file; i++)
		fprintf(ftmp, "%d ", arr[i]);
	fclose(ftmp);

	// Input the other half of file data to array 'arr'
	for(int i = 0; i < size_arr; i++){
		fscanf(fin, "%d", &tmp);
		arr[i] = tmp;
	}
	// Sort array 'arr'
	heap_sort(arr, size_arr);

	fclose(fin);

	merge(file_tmp, size_file, arr, size_arr, file_out);
	free(arr);
}

void merge(char *file_tmp, int size_file, int *arr, int size_arr, char *file_out)
{
	FILE *fout = fopen(file_out, "w");
	FILE *ftmp = fopen(file_tmp, "r");
	if(!fout || !ftmp){ printf("Error open file!\n"); exit(1); }

	fprintf(fout, "%d\n", size_file + size_arr);

	int tmp;
	int count = 0;

	fscanf(ftmp, "%d", &tmp);
	while(size_file > 0 && count < size_arr){
		if(tmp < arr[count]){
			fprintf(fout, "%d ", tmp);
			fscanf(ftmp, "%d", &tmp);
			size_file--;
		}
		else
			fprintf(fout, "%d ", arr[count++]);
	}
	while(size_file-- > 0){
		fprintf(fout, "%d ", tmp);
		fscanf(ftmp, "%d", &tmp);
	}
	while(count < size_arr)
		fprintf(fout, "%d ", arr[count++]);
	
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

void adjust_heap(int arr[], int root, int n)
{
	if(root > n / 2 - 1) return;

	int left = 2 * root + 1, right = left + 1;
	int tmp = (arr[root] < arr[left] ? left : root);
	if(right < n)
		tmp = (arr[tmp] < arr[right] ? right : tmp);

	if(tmp != root){
		swap(&arr[root], &arr[tmp]);
		adjust_heap(arr, tmp, n);
	}
}

void heap_sort(int arr[], int n)
{
	for(int i = (n - 1) / 2; i >= 0; i--)
		adjust_heap(arr, i, n);

	for(int i = n - 1; i > 0; i--){
		swap(&arr[i], &arr[0]);
		adjust_heap(arr, 0, i);
	}
}

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}