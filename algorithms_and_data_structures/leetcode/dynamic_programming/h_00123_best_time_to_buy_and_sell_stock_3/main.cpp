#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int days = prices.size();
        if (days < 2)
            return 0;

        vector<vector<int>> dp(days, vector<int>(5, 0));
        dp[0][0] = 0;          // 不操作的余额
        dp[0][1] = -prices[0]; // 第1次买入后的余额
        dp[0][2] = 0;          // 第1次卖出后的余额
        dp[0][3] = -prices[0]; // 第2次买入后的余额
        dp[0][4] = 0;          // 第2次卖出后的余额

        for (int i = 1; i < days; i++)
        {
            dp[i][0] = dp[i - 1][0];
            dp[i][1] = max(dp[i - 1][0] - prices[i], dp[i - 1][1]);
            dp[i][2] = max(dp[i - 1][1] + prices[i], dp[i - 1][2]);
            dp[i][3] = max(dp[i - 1][2] - prices[i], dp[i - 1][3]);
            dp[i][4] = max(dp[i - 1][3] + prices[i], dp[i - 1][4]);
        }

        return dp[days - 1][4];
    }
};

class SolutionRefined
{
public:
    int maxProfit(vector<int> &prices)
    {
        if (prices.size() == 0)
            return 0;

        vector<int> dp(5, 0);
        dp[1] = -prices[0];
        dp[3] = -prices[0];

        for (int i = 1; i < prices.size(); i++)
        {
            dp[1] = max(dp[1], dp[0] - prices[i]);
            dp[2] = max(dp[2], dp[1] + prices[i]);
            dp[3] = max(dp[3], dp[2] - prices[i]);
            dp[4] = max(dp[4], dp[3] + prices[i]);
        }
        return dp[4];
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {3, 3, 5, 0, 0, 3, 1, 4},       // 6
        {1, 2, 3, 4, 5},                // 4
        {7, 6, 4, 3, 1},                // 0
        {3, 2, 6, 5, 0, 3},             // 7
        {6, 1, 3, 2, 4, 7},             // 7
        {2, 1, 4, 5, 2, 9, 7},          // 11
        {1, 2, 4, 2, 5, 7, 2, 4, 9, 0}, // 13
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maxProfit(inputs[group]) << endl;

    return 0;
}
