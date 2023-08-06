#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int dp[nums.size()];
        int result = 1;
        for (int i = 0; i < nums.size(); i++)
        {
            dp[i] = 1;
            for (int j = 0; j < i; j++)
                if (nums[i] > nums[j])
                    dp[i] = max(dp[i], dp[j] + 1);

            result = max(result, dp[i]);
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {10, 9, 2, 5, 3, 7, 101, 18}, // 4
        {0, 1, 0, 3, 2, 3},           // 4
        {7, 7, 7, 7, 7, 7, 7},        // 1
        {1, 3, 6, 7, 9, 4, 10, 5, 6}, // 6
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.lengthOfLIS(nums[group]) << endl;

    return 0;
}
