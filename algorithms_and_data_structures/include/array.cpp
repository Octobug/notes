#include <iostream>

#include "array.h"

using namespace std;

void output(vector<int> &arr)
{
    cout << '[';
    for (int i = 0; i < arr.size(); ++i)
    {
        cout << arr[i];
        if (i != arr.size() - 1)
        {
            cout << ',';
        }
    }
    cout << ']' << endl;
}
