#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int minOperations(vector<int> &nums, int k)
    {
        int result = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] < k)
                result++;
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {2, 11, 10, 1, 3}, // 3
        {1, 1, 2, 4, 9},   // 0
        {1, 1, 2, 4, 9},   // 4
    };

    vector<int> ks = {10, 1, 9};
    int group = getGroup();

    Solution s;
    cout << s.minOperations(nums[group], ks[group]) << endl;

    return 0;
}
