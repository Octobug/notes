#include <iostream>

#include "array.h"

using namespace std;

void output(vector<int> &numbers)
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

void output(vector<double> &numbers)
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
void output(vector<string> &strs)
{
    cout << '[';
    for (int i = 0; i < strs.size(); i++)
    {
        cout << strs[i];
        if (i != strs.size() - 1)
        {
            cout << ',';
        }
    }
    cout << ']' << endl;
}

void output2d(vector<vector<int>> &matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        output(matrix[i]);
    }
}

void output2d(vector<vector<string>> &matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        output(matrix[i]);
    }
}

void swap(vector<int> &numbers, int index_l, int index_r)
{
    int tmp = numbers[index_l];
    numbers[index_l] = numbers[index_r];
    numbers[index_r] = tmp;
}
