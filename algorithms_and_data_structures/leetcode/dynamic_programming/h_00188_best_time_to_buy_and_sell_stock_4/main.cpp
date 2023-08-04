#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        if (prices.size() == 0)
            return 0;

        int status = 2 * k + 1;
        vector<int> dp(status, 0);

        for (int i = 1; i < status; i += 2)
            dp[i] = -prices[0];

        int sell;
        for (int i = 1; i < prices.size(); i++)
        {
            sell = -1;
            for (int j = 1; j < status; j++)
            {
                dp[j] = max(dp[j], dp[j - 1] + sell * prices[i]);
                sell *= -1;
            }
        }

        return dp[status - 1];
    }
};

int main()
{
    vector<vector<int>> prices = {
        {2, 4, 1},          // 2
        {3, 2, 6, 5, 0, 3}, // 7
    };
    vector<int> ks = {2, 2};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maxProfit(ks[group], prices[group]) << endl;

    return 0;
}
