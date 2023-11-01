#ifndef __ARRAY__
#define __ARRAY__

#include <vector>

using namespace std;

void output(int numbers[], int size);
void output2d(int *matrix, int m, int n);

template <typename T>
void output(vector<T> &numbers);

template <typename T>
void output2d(vector<vector<T>> &matrix);

void swap(vector<int> &numbers, int index_l, int index_r);

#endif
