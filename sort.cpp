#include "iostream"
#include "vector"
#include "fstream"

using namespace std;

#define SIZE 1000000	// number of interger
#define MIN -2147483648	// min signed 32-bit number
#define MAX 2147483647	// max signed 32-bit number
#define CUR_MIN_SIZE 5000	// max size of vector cur_min

typedef struct _Node
{
	long value;
	long count;	// Number of integer equal 'value'
}Node;

/*************************** APIs ***************************/
// Input data from file to vector cur_min, if sizeof cur_min > 0 return true else return false
bool input(char *fileName, vector<Node> &cur_min, long &min);
// Write data from vector cur_min to file
void output(char *fileName, vector<Node> cur_min);
// Insert element to vector cur_min
void insert(vector<Node> &cur_min, long newValue);
// Return index to insert target into vector cur_min, if not existed return -1
int find_value(vector<Node> cur_min, long target);
// Return index of target in vector cur_min, if not existed return -1
int existed(vector<Node> cur_min, long target);

/*************************** MAIN ***************************/
int main()
{
	long min = MIN;
	char *file_in = "input.txt", *file_out = "output.txt";

	// Write all element equal MIN in file input to file output
	fstream fin (file_in, fstream::in);
	ofstream fout (file_out, ofstream::trunc);
	for(long i = 0; i < SIZE; i++){
		fin >> min;
		if(min == MIN) fout << MIN << " ";
	}
	fin.close();
	fout.close();

	// Resolve all element larger MIN
	min = MIN;
	vector<Node> cur_min(0);
	while(1){
		// if sizeof cur_min equal 0 then break of loop
		if(!input("input.txt", cur_min, min)) break;
		output("output.txt", cur_min);
		cur_min.clear();
	}
}

/**************************************************************/
bool input(char *fileName, vector<Node> &cur_min, long &min)
{
	fstream f;
	f.open(fileName, fstream::in);

	long tmp;
	long count = 0;
	while(count < SIZE){
		f >> tmp;

		int target = existed(cur_min, tmp);
		// if target is existing
		if(target != -1) cur_min[target].count++;
		// 
		else if(cur_min.size() < CUR_MIN_SIZE && tmp > min)
			cur_min.insert(cur_min.begin() + find_value(cur_min, tmp), {tmp, 1});
		// if tmp < max element of cur_min remove max element, insert tmp to cur_min
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
	// Binary search
	int l = 0, r = cur_min.size() - 1;
	int cur = (l + r) / 2;
	while(l <= r){
		if(cur_min[cur].value == target) return cur;
		else if(cur_min[cur].value > target){
			r = cur - 1;
			cur = (l + r) / 2;
		}
		else{
			l = cur + 1;
			cur = (l + r) / 2;
		}
	}
	return -1;
}