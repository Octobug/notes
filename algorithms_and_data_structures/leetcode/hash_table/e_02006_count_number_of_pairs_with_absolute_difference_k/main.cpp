#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int countKDifference(vector<int> &nums, int k)
    {
        int table[101] = {0};

        for (int i = 0; i < nums.size(); i++)
            table[nums[i]]++;

        int result = 0;

        for (int i = 1; i < 101 && i + k < 101; i++)
            result += table[i] * table[i + k];

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {1, 2, 2, 1},    // 4
        {1, 3},          // 0
        {3, 2, 1, 5, 4}, // 3
    };
    vector<int> ks = {1, 3, 2};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.countKDifference(nums[group], ks[group]) << endl;

    return 0;
}
