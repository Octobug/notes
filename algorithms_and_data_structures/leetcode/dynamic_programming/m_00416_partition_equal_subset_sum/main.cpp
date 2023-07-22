#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        int sum = 0;
        for (auto num : nums)
            sum += num;

        if (sum % 2 == 1)
            return false;

        int half = sum / 2;

        vector<int> dp(half + 1, 0);
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = half; j >= nums[i]; j--)
            {
                dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
                if (dp[j] == half)
                    return true;
            }
        }
        return false;
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {1, 5, 11, 5},
        {1, 2, 3, 5},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.canPartition(inputs[group]) << endl;

    return 0;
}
