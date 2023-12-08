#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int minOperations(vector<int> &nums)
    {
        int result = 0;

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] <= nums[i - 1])
            {
                int diff = nums[i - 1] - nums[i] + 1;
                nums[i] += diff;
                result += diff;
            }
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {1, 1, 1},       // 3
        {1, 5, 2, 4, 1}, // 14
        {8},             // 0
    };

    int group = getGroup();

    Solution s;
    cout << s.minOperations(nums[group]) << endl;

    return 0;
}
