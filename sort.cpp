#include "iostream"
#include "fstream"
#include "algorithm"

#include "string.h"

using namespace std;

void msort(char *file_in, char *file_out);
void merge_file(char *file_tmp0, long size0, char *file_tmp1, int size1, char *file_out);
void merge(char *file_tmp, long size_file, long arr[], long size_arr, char *file_out);
void remove_file(char *file_name);

int main()
{
	msort("input.txt", "output.txt");
	int i; cin >> i;
	return 0;
}

void msort(char *file_in, char *file_out)
{
	fstream fin (file_in, fstream::in);
	long size;
	fin >> size;

	char *file_tmp0 = "tmp0~.txt", *file_tmp1 = "tmp1~.txt";
	ofstream ftmp[2];
	ftmp[0].open(file_tmp0, ofstream::trunc);
	ftmp[1].open(file_tmp1, ofstream::trunc);

	long tmp;
	long size_file = size / 3;

	long *arr = new long[size_file];
	for(int times = 0; times < 2; times++){
		// Input 1/3 of file data to array 'arr'
		for(long i = 0; i < size_file; i++){
			fin >> tmp;
			arr[i] = tmp;
		}
		// Sort array 'arr'
		sort(arr, arr + size_file);
		for(long i = 0; i < size_file; i++)
			ftmp[times] << arr[i] << " ";
		ftmp[times].close();
	}
	delete[] arr;

	// Input the other 1/3 of file data to array 'arr'
	long size_arr = size - 2 * size_file;
	arr = new long[size_arr];
	for(long i = 0; i < size_arr; i++){
		fin >> tmp;
		arr[i] = tmp;
	}
	sort(arr, arr + size_arr);
	
	char *file_tmp = "tmp~.txt";
	merge_file(file_tmp0, size_file, file_tmp1, size_file, file_tmp);
	merge(file_tmp, size - size_arr, arr, size_arr, file_out);
	delete[] arr;
}

void merge_file(char *file_tmp0, long size0, char *file_tmp1, int size1, char *file_out)
{
	fstream f1 (file_tmp0, fstream::in);
	fstream f2 (file_tmp1, fstream::in);
	ofstream fout (file_out, ofstream::trunc);

	long tmp1, tmp2;
	f1 >> tmp1; f2 >> tmp2;
	while(size0 > 0 && size1 > 0){
		if(tmp1 < tmp2){
			fout << tmp1 << " ";
			f1 >> tmp1;
			size0--;
		}
		else{
			fout << tmp2 << " ";
			f2 >> tmp2;
			size1--;
		}
	}
	while(size0-- > 0){
		fout << tmp1 << " ";
		f1 >> tmp1;
	}
	while(size1-- > 0){
		fout << tmp2 << " ";
		f2 >> tmp2;
	}

	f1.close(); f2.close(); fout.close();
	remove_file(file_tmp0);
	remove_file(file_tmp1);
}

void merge(char *file_tmp, long size_file, long arr[], long size_arr, char *file_out)
{
	fstream ftmp (file_tmp, fstream::in);
	ofstream fout (file_out, ofstream::trunc);
	fout << size_file + size_arr << endl;

	long tmp1;
	long count = 0;
	ftmp >> tmp1;
	while(size_file > 0 && count < size_arr){
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
	while(count < size_arr)
		fout << arr[count++] << " ";

	ftmp.close();
	fout.close();
	remove_file(file_tmp);
}

void remove_file(char *file_name)
{
	char tmp[20] = "rm ";
	strcat(tmp, file_name);
	system(tmp);
}