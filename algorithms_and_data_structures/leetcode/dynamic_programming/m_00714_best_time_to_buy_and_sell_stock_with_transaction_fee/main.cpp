#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices, int fee)
    {
        int dp[prices.size()][2];
        dp[0][0] = -prices[0]; // 持有股票的账户余额
        dp[0][1] = 0;          // 不持有股票的账户余额

        for (int i = 1; i < prices.size(); i++)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i] - fee);
        }
        return dp[prices.size() - 1][1];
    }
};

class SolutionRefined
{
public:
    int maxProfit(vector<int> &prices, int fee)
    {
        int dp[2];
        dp[0] = -prices[0]; // 持有股票的账户余额
        dp[1] = 0;          // 不持有股票的账户余额

        for (int i = 1; i < prices.size(); i++)
        {
            dp[0] = max(dp[0], dp[1] - prices[i]);
            dp[1] = max(dp[1], dp[0] + prices[i] - fee);
        }
        return dp[1];
    }
};

int main()
{
    vector<vector<int>> prices = {
        {1, 3, 2, 8, 4, 9},  // 8
        {1, 3, 7, 5, 10, 3}, // 6
    };
    vector<int> fees = {2, 3};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maxProfit(prices[group], fees[group]) << endl;

    return 0;
}
