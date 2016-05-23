#include "iostream"
#include "fstream"
#include "algorithm"

#include "string.h"

#define SIZE 1000000
#define HALF_SIZE SIZE / 2

using namespace std;

void msort(char *file_in, char *file_out);
void merge(char *file_tmp, long arr[], char *file_out);
void remove_file(char *file_name);

int main()
{
	msort("input.txt", "output.txt");
	return 0;
}

void msort(char *file_in, char *file_out)
{
	fstream fin (file_in, fstream::in);

	char *file_tmp = "tmp~.txt";
	ofstream ftmp (file_tmp, ofstream::trunc);

	long tmp;

	long arr[HALF_SIZE];
	// Input, sort and write to file
	for(long i = 0; i < HALF_SIZE; i++){
		fin >> tmp;
		arr[i] = tmp;
	}
	sort(arr, arr + HALF_SIZE);
	for(long i = 0; i < HALF_SIZE; i++)
		ftmp << arr[i] << " ";
	fin.close();

	// Input and sort
	// HALF_SIZE = size - HALF_SIZE;
	for(long i = 0; i < HALF_SIZE; i++){
		fin >> tmp;
		arr[i] = tmp;
	}
	sort(arr, arr + HALF_SIZE);
		
	merge(file_tmp, arr, file_out);
	remove_file(file_tmp);
}

void merge(char *file_tmp, long arr[], char *file_out)
{
	fstream ftmp (file_tmp, fstream::in);
	ofstream fout (file_out, ofstream::trunc);

	long tmp1;
	long count = 0, size_file = HALF_SIZE;
	ftmp >> tmp1;
	while(size_file > 0 && count < HALF_SIZE){
		if(tmp1 < arr[count]){
			fout << tmp1 << " ";
			ftmp >> tmp1;
			size_file--;
		}
		else{
			fout << arr[count] << " ";
			count++;
		}
	}
	while(size_file-- > 0){
		fout << tmp1 << " ";
		ftmp >> tmp1;
	}
	while(count < HALF_SIZE)
		fout << arr[count++] << " ";

	ftmp.close();
	fout.close();
}

void remove_file(char *file_name)
{
	char tmp[20] = "rm ";
	strcat(tmp, file_name);
	system(tmp);
}