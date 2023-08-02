#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int rob(vector<int> &nums)
    {
        if (nums.size() == 1)
            return nums[0];

        int dp[nums.size()];
        dp[0] = nums[0];
        dp[1] = max(dp[0], nums[1]);

        for (int i = 2; i < nums.size(); i++)
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);

        return dp[nums.size() - 1];
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {1, 2, 3, 1},    // 4
        {2, 7, 9, 3, 1}, // 12
        {1, 2, 1, 1},    // 3
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.rob(inputs[group]) << endl;

    return 0;
}
