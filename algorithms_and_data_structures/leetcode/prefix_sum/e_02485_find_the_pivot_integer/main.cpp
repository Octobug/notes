#include <iostream>
#include <vector>
#include <math.h>
#include "input.h"

using namespace std;

class Solution
{
public:
    int pivotInteger(int n)
    {
        int sum = (n * (n + 1)) / 2;
        int root = sqrt(sum);
        if (root * root == sum)
            return root;
        else
            return -1;
    }
};

int main()
{
    vector<int> ns = {
        8, // 6
        1, // 1
        4, // -1
    };

    int group = getGroup();
    Solution s;
    cout << s.pivotInteger(ns[group]) << endl;

    return 0;
}
