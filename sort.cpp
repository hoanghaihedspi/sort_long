#include "iostream"
#include "vector"
#include "fstream"

using namespace std;

#define SIZE 1000000
#define MIN -2147483648
#define MAX 2147483647
#define CUR_MIN_SIZE 1000

typedef struct _Node
{
	long value;
	long count;
}Node;

bool input(char *fileName, vector<Node> &cur_min, long &min);
void output(char *fileName, vector<Node> cur_min);
void insert(vector<Node> &cur_min, long newValue);
int find_value(vector<Node> cur_min, long target);
int existed(vector<Node> cur_min, long target);

int main()
{
	long min = MIN;
	char *file_in = "input.txt", *file_out = "output.txt";

	fstream fin (file_in, fstream::in);
	ofstream fout (file_out, ofstream::trunc);
	for(long i = 0; i < SIZE; i++){
		fin >> min;
		if(min == MIN) fout << MIN << " ";
	}
	fin.close();
	fout.close();

	min = MIN;
	vector<Node> cur_min(0);
	while(1){
		if(!input("input.txt", cur_min, min)) break;
		output("output.txt", cur_min);
		cur_min.clear();
	}
}

bool input(char *fileName, vector<Node> &cur_min, long &min)
{
	fstream f;
	f.open(fileName, fstream::in);

	long tmp;
	long count = 0;
	while(count < SIZE){
		f >> tmp;

		int target = existed(cur_min, tmp);
		if(target != -1) cur_min[target].count++;

		else if(cur_min.size() < CUR_MIN_SIZE && tmp > min)
			cur_min.insert(cur_min.begin() + find_value(cur_min, tmp), {tmp, 1});

		else if(tmp > min && tmp < cur_min[cur_min.size() - 1].value)
			insert(cur_min, tmp);

		count++;
	}

	f.close();

	if(cur_min.size()){
		min = cur_min[cur_min.size() - 1].value;
		return true;
	}
	else return false;
}

void output(char *fileName, vector<Node> cur_min)
{
	ofstream f;
	f.open(fileName, ofstream::app);

	for(int i = 0; i < cur_min.size(); i++)
		for(long j = 0; j < cur_min[i].count; j++)
			f << cur_min[i].value << " ";

	f.close();
}

void insert(vector<Node> &cur_min, long newValue)
{
	cur_min.pop_back();
	cur_min.insert(cur_min.begin() + find_value(cur_min, newValue), {newValue, 1});
}

int find_value(vector<Node> cur_min, long target)
{
	int res = 0;
	for(res = 0; res < cur_min.size() && cur_min[res].value < target; res++);
	return res;
}

int existed(vector<Node> cur_min, long target)
{
	// Cai tien bang tim kiem nhi phan
	for(int i = 0; i < cur_min.size(); i++)
		if(target == cur_min[i].value) return i;
	return -1;
}