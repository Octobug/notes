#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int xorOperation(int n, int start)
    {
        int result = start;
        int num = start;

        for (int i = 1; i < n; i++)
        {
            num += 2;
            result ^= num;
        }

        return result;
    }
};

int main()
{
    vector<int> ns = {
        5,
        4,
    };
    vector<int> starts = {
        0,
        3,
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.xorOperation(ns[group], starts[group]) << endl;

    return 0;
}
