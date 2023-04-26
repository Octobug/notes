#include <iostream>

#include "array.h"

using namespace std;

void output(vector<int> &numbers)
{
    cout << '[';
    for (int i = 0; i < numbers.size(); ++i)
    {
        cout << numbers[i];
        if (i != numbers.size() - 1)
        {
            cout << ',';
        }
    }
    cout << ']' << endl;
}

void swap(vector<int> &numbers, int index_l, int index_r)
{
    int tmp = numbers[index_l];
    numbers[index_l] = numbers[index_r];
    numbers[index_r] = tmp;
}
