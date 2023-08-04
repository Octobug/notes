#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int dp[prices.size()][3];
        dp[0][0] = -prices[0]; // 持有股票的账户余额
        dp[0][1] = 0;          // 不持有股票的账户余额
        dp[0][2] = 0;          // 冻结状态的账户余额

        for (int i = 1; i < prices.size(); i++)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][2] - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
            dp[i][2] = max(dp[i - 1][2], dp[i - 1][1]);
        }

        return dp[prices.size() - 1][1];
    }
};

class Solution4s
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        if (n == 0)
            return 0;

        vector<vector<int>> dp(n, vector<int>(4, 0));
        dp[0][0] -= prices[0]; // 持股票

        for (int i = 1; i < n; i++)
        {
            dp[i][0] = max(dp[i - 1][0],
                           max(dp[i - 1][3] - prices[i],
                               dp[i - 1][1] - prices[i]));
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);
            dp[i][2] = dp[i - 1][0] + prices[i];
            dp[i][3] = dp[i - 1][2];
        }

        return max(dp[n - 1][3], max(dp[n - 1][1], dp[n - 1][2]));
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {1, 2, 3, 0, 2}, // 3
        {1},             // 0
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maxProfit(inputs[group]) << endl;

    return 0;
}
