#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int rob(vector<int> &nums)
    {
        if (nums.size() == 0)
            return 0;
        if (nums.size() == 1)
            return nums[0];

        int result1 = robRange(nums, 0, nums.size() - 2);
        int result2 = robRange(nums, 1, nums.size() - 1);

        return max(result1, result2);
    }

    int robRange(vector<int> &nums, int start, int end)
    {
        if (end == start)
            return nums[start];

        int dp[nums.size()];
        dp[start] = nums[start];
        dp[start + 1] = max(nums[start], nums[start + 1]);
        for (int i = start + 2; i <= end; i++)
        {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[end];
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {2, 3, 2},             // 3
        {1, 2, 3, 1},          // 4
        {1, 2, 3},             // 3
        {1, 2, 1, 1},          // 3
        {200, 3, 140, 20, 10}, // 340
        {1, 1, 1, 2},          // 3
        {2, 2, 4, 3, 2, 5},    // 10
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.rob(inputs[group]) << endl;

    return 0;
}
