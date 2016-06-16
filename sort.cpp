#include "iostream"
#include "fstream"
#include "algorithm"

#include "string.h"

using namespace std;

void msort(char *file_in, char *file_out);
void merge(char *file_tmp, int size_file, int *arr, int size_arr, char *file_out);
void remove_file(char *file_name);

int main()
{
	msort("input.txt", "output.txt");
	return 0;
}

void msort(char *file_in, char *file_out)
{
	fstream fin (file_in, fstream::in);
	int size;
	fin >> size;
	int size_file = size / 2;
	int size_arr = size - size_file;

	char *file_tmp = "tmp~.txt";
	ofstream ftmp (file_tmp, ofstream::trunc);

	int tmp;
	int *arr = new int[size_arr];
	// Input, sort and write to file
	for(int i = 0; i < size_file; i++){
		fin >> tmp;
		arr[i] = tmp;
	}
	sort(arr, arr + size_file);
	for(int i = 0; i < size_file; i++)
		ftmp << arr[i] << " ";
	ftmp.close();

	// Input and sort
	for(int i = 0; i < size_arr; i++){
		fin >> tmp;
		arr[i] = tmp;
	}
	fin.close();
	sort(arr, arr + size_arr);
		
	merge(file_tmp, size_file, arr, size_arr, file_out);
	remove_file(file_tmp);
	delete[] arr;
}

void merge(char *file_tmp, int size_file, int *arr, int size_arr, char *file_out)
{
	fstream ftmp (file_tmp, fstream::in);
	ofstream fout (file_out, ofstream::trunc);
	fout << size_file + size_arr << endl;

	int tmp;
	int count = 0;
	ftmp >> tmp;
	while(size_file > 0 && count < size_arr){
		if(tmp < arr[count]){
			fout << tmp << " ";
			ftmp >> tmp;
			size_file--;
		}
		else
			fout << arr[count++] << " ";
	}
	while(size_file-- > 0){
		fout << tmp << " ";
		ftmp >> tmp;
	}
	while(count < size_arr)
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