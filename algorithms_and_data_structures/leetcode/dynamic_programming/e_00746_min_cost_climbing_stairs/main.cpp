#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int minCostClimbingStairs(vector<int> &cost)
    {
        int dp[cost.size() + 1];
        dp[0] = 0;
        dp[1] = 0;

        for (int i = 2; i <= cost.size(); i++)
            dp[i] = min(dp[i - 2] + cost[i - 2], dp[i - 1] + cost[i - 1]);

        return dp[cost.size()];
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {10, 15, 20},
        {1, 100, 1, 1, 1, 100, 1, 1, 100, 1},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.minCostClimbingStairs(inputs[group]) << endl;

    return 0;
}
