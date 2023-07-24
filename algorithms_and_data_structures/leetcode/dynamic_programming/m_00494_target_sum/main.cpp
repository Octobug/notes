#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int findTargetSumWays(vector<int> &nums, int target)
    {
        int sum = 0;
        for (auto num : nums)
            sum += num;

        int bag = sum - target;
        if (sum < target || bag % 2 == 1)
            return 0;

        bag /= 2;
        vector<int> dp(bag + 1, 0);
        dp[0] = 1;

        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = bag; j >= nums[i]; j--)
            {
                dp[j] += dp[j - nums[i]];
            }
        }

        return dp[bag];
    }
};

int main()
{
    vector<vector<vector<int>>> inputs = {
        {{1, 1, 1, 1, 1}, {3}},                // 5
        {{1}, {1}},                            // 1
        {{1, 0}, {1}},                         // 2
        {{0, 0, 0, 0, 0, 0, 0, 0, 1}, {1}},    // 256
        {{1, 2, 1}, {0}},                      // 2
        {{7, 9, 3, 8, 0, 2, 4, 8, 3, 9}, {0}}, // 0
        {{9, 7, 0, 3, 9, 8, 6, 5, 7, 6}, {2}}, // 40
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.findTargetSumWays(inputs[group][0], inputs[group][1][0]) << endl;

    return 0;
}
