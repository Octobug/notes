#include <iostream>
#include <vector>

using namespace std;

class SolutionDP
{
public:
    int maxProfit(vector<int> &prices)
    {
        int len = prices.size();
        if (len < 2)
            return 0;

        vector<vector<int>> dp(len, vector<int>(2));
        dp[0][0] = -prices[0]; // 持有股票的账户余额
        dp[0][1] = 0;          // 不持有股票的账户余额

        for (int i = 1; i < len; i++)
        {
            dp[i][0] = max(dp[i - 1][0], -prices[i]);
            dp[i][1] = max(dp[i - 1][1], prices[i] + dp[i - 1][0]);
        }

        return dp[len - 1][1];
    }
};

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        if (prices.size() == 1)
            return 0;

        int lower = prices[0], profit = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            profit = max(profit, prices[i] - lower);
            lower = min(lower, prices[i]);
        }

        return profit;
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {7, 1, 5, 3, 6, 4}, // 5
        {7, 6, 4, 3, 1},    // 0
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maxProfit(inputs[group]) << endl;

    return 0;
}
