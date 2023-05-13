#ifndef __ARRAY__
#define __ARRAY__

#include <vector>

using namespace std;

void output(vector<int> &numbers);
void output(vector<double> &numbers);
void output(vector<char> &chars);
void output(vector<string> &strs);
void output2d(vector<vector<int>> &matrix);
void output2d(vector<vector<string>> &matrix);
void swap(vector<int> &numbers, int index_l, int index_r);

#endif
