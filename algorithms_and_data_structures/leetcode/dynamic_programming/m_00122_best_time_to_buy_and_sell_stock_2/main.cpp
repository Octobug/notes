#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
        dp[0][0] = -prices[0]; // 持有股票的账户余额
        dp[0][1] = 0;          // 不持有股票的账户余额

        for (int i = 1; i < prices.size(); i++)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
        }
        return dp[prices.size() - 1][1];
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {7, 1, 5, 3, 6, 4}, // 7
        {1, 2, 3, 4, 5},    // 4
        {7, 6, 4, 3, 1},    // 0
        {1, 2},             // 1
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maxProfit(inputs[group]) << endl;

    return 0;
}
