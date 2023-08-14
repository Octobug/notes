#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        vector<int> dp(nums.size(), 0);

        dp[0] = nums[0];
        int result = dp[0];

        for (int i = 1; i < nums.size(); i++)
        {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            result = max(result, dp[i]);
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {-2, 1, -3, 4, -1, 2, 1, -5, 4},
        {1},
        {5, 4, -1, 7, 8},
        {-2, -1},
        {8, -19, 5, -4, 20},
        {1, -1, -2},
        {0, -3, 1, 1},
        {-3, 2, -1},
        {-1, -2, -2, -2, 3, 2, -2, 0},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maxSubArray(inputs[group]) << endl;

    return 0;
}
