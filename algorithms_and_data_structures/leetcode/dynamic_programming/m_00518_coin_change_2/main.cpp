#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int change(int amount, vector<int> &coins)
    {
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;

        for (int i = 0; i < coins.size(); i++)
        {
            for (int j = coins[i]; j <= amount; j++)
            {
                dp[j] += dp[j - coins[i]];
            }
        }

        return dp[amount];
    }
};

int main()
{
    vector<vector<int>> coins = {
        {1, 2, 5},
        {2},
        {10},
    };
    vector<int> amounts = {5, 3, 10};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.change(amounts[group], coins[group]) << endl;

    return 0;
}
