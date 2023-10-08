#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int differenceOfSums(int n, int m)
    {
        int num1 = 0, num2 = 0;

        for (int i = 1; i <= n; i++)
        {
            if (i % m == 0)
                num2 += i;
            else
                num1 += i;
        }

        return num1 - num2;
    }
};

int main()
{
    vector<int> ns = {
        10, // 19
        5,  // 15
        5,  // -15
    };
    vector<int> ms = {
        3,
        6,
        1,
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.differenceOfSums(ns[group], ms[group]) << endl;

    return 0;
}
