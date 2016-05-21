#include "stdio.h"
#include "stdlib.h"

#define PIVOT_L -2147483648
#define PIVOT_R 2147483647
#define MAX_LENGTH 5000

long input(char *fileName, long arr[], long pivot_l, long pivot_r);
void output(char *fileName, long arr[], long length);
void special(char *file_in, char *file_out, long target);
void quickSort(long arr[], long left, long right);
void swap(long *a, long *b);

int main()
{
	char *file_in = "input.txt", *file_out = "output.txt";
	long arr[MAX_LENGTH];
	long pivot_l = PIVOT_L, pivot_r = pivot_l + MAX_LENGTH, pre_pivot = 0;
	long length = 0;

	while(1){
		length = input(file_in, arr, pivot_l, pivot_r);
		while(length <= 0){	// Qua so phan tu hoac ko co phan tu nao
			if(length == -1){
				quickSort(arr, 0, MAX_LENGTH - 1);
				if(arr[0] == arr[MAX_LENGTH - 1]){	// Co nhieu hon MAX_LENGTH so bang nhau
					special(file_in, file_out, arr[0]);
					break;
				}
				else if(pre_pivot){
					long tmp = pre_pivot;
					pre_pivot = pivot_r;
					pivot_r = (tmp + pivot_r) / 2;
				}
				else
					pivot_r = (pivot_r + pivot_l) / 2;
			}
			else if(length == 0){
				pivot_l = pivot_r + 1;
				pre_pivot = pivot_r;
				pivot_r = (pivot_r + PIVOT_R) / 2;
			}
			length = input(file_in, arr, pivot_l, pivot_r);
		}

		output(file_out, arr, length);

		if(pivot_r == PIVOT_R) break;
		else{
			pre_pivot = 0;
			pivot_l = pivot_r + 1;
			pivot_r = pivot_r + MAX_LENGTH >= PIVOT_R ? PIVOT_R : pivot_r + MAX_LENGTH;
		}
	}

	return 0;
}

long input(char *fileName, long arr[], long pivot_l, long pivot_r)
{
	FILE *f = fopen(fileName, "r");
	if(!f){ printf("Error open file \"%s\"!\n", fileName); exit(1); }

	long count = 0, tmp;
	while(count < MAX_LENGTH && !feof(f)){
		fscanf(f, "%ld", &tmp);
		if(tmp >= pivot_l && tmp <= pivot_r) arr[count++] = tmp;
	}

	if(count == MAX_LENGTH && !feof(f))	// Qua so phan tu
		return -1;
	else return count;
}

void output(char *fileName, long arr[], long length)
{
	quickSort(arr, 0, length - 1);

	FILE *f = fopen(fileName, "a+");
	if(!f){ printf("Error open file \"%s\"!\n", fileName); exit(1); }

	for(long i = 0; i < length; i++)
		fprintf(f, "%ld ", arr[i]);

	fclose(f);
}

void special(char *file_in, char *file_out, long target)
{
	FILE *f_in = fopen(file_in, "r");
	if(!f_in){ printf("Error open file \"%s\"!\n", file_in); exit(1); }
	FILE *f_out = fopen(file_out, "a+");
	if(!f_out){ printf("Error open file \"%s\"!\n", file_out); exit(1); }

	long tmp;
	while(!feof(f_in)){
		fscanf(f_in, "%ld", &tmp);
		if(tmp == target)
			fprintf(f_out, "%ld ", tmp);
	}
}

void quickSort(long arr[], long left, long right)
{
	if(left >= right) return;

	long i = left + 1, j = right;
	long key = arr[left];

	do{
		for( ; i < right && arr[i] < key; ++i);
		for( ; j > left && arr[j] > key; --j);
		swap(&arr[i], &arr[j]);
	}while(i < j);
	swap(&arr[i], &arr[j]);
	swap(&arr[left], &arr[j]);

	quickSort(arr, left, j - 1);
	quickSort(arr, j + 1, right);
}

void swap(long *a, long *b)
{
	long tmp = *a;
	*a = *b;
	*b = tmp;
}