#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        if (amount == 0)
            return 0;
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;

        for (int i = 0; i < coins.size(); i++)
            for (int j = coins[i]; j <= amount; j++)
                if (dp[j - coins[i]] != INT_MAX)
                    dp[j] = min(dp[j], dp[j - coins[i]] + 1);

        return dp[amount] != INT_MAX ? dp[amount] : -1;
    }
};

int main()
{
    vector<vector<int>> coins = {
        {1, 2, 5},           // 3
        {2},                 // -1
        {1},                 // 0
        {2},                 // -1
        {2, 5, 10, 1},       // 4
        {186, 419, 83, 408}, // 20
    };
    vector<int> amounts = {11, 3, 0, 1, 27, 6249};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.coinChange(coins[group], amounts[group]) << endl;

    return 0;
}
