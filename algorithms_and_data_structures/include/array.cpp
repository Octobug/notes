#include <iostream>
#include "array.h"

using namespace std;

void output(int numbers[], int size)
{
    cout << '[';
    for (int i = 0; i < size; i++)
    {
        cout << numbers[i];
        if (i < size - 1)
        {
            cout << ',';
        }
    }
    cout << ']' << endl;
}

void output2d(int *matrix, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        output(&matrix[i], n);
    }
}

template <typename T>
void output(vector<T> &numbers)
{
    cout << '[';
    for (int i = 0; i < numbers.size(); i++)
    {
        cout << numbers[i];
        if (i != numbers.size() - 1)
        {
            cout << ',';
        }
    }
    cout << ']' << endl;
}
template void output(vector<bool> &numbers);
template void output(vector<char> &numbers);
template void output(vector<double> &numbers);
template void output(vector<string> &numbers);

template <typename T>
void output2d(vector<vector<T>> &matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        output(matrix[i]);
    }
}
template void output2d(vector<vector<char>> &matrix);
template void output2d(vector<vector<int>> &matrix);
template void output2d(vector<vector<string>> &matrix);

void swap(vector<int> &numbers, int index_l, int index_r)
{
    int tmp = numbers[index_l];
    numbers[index_l] = numbers[index_r];
    numbers[index_r] = tmp;
}
