#include <iostream>
#include <vector>
#include "array.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    int maxSatisfaction(vector<int> &satisfaction)
    {
        sort(satisfaction.begin(), satisfaction.end());
        int len = satisfaction.size();
        int dp[len];
        dp[len - 1] = satisfaction[len - 1];

        for (int i = len - 2; i >= 0; i--)
            dp[i] = satisfaction[i] + dp[i + 1];

        int result = 0;
        int timeCoef = 1;
        for (int i = 0; i < satisfaction.size(); i++)
        {
            if (dp[i] < 0)
                continue;

            result += satisfaction[i] * timeCoef;
            timeCoef++;
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> satisfactions = {
        {-1, -8, 0, 5, -9}, // 14
        {4, 3, 2},          // 20
        {-1, -4, -5},       // 0
    };
    int group = getGroup();

    Solution s;
    cout << s.maxSatisfaction(satisfactions[group]) << endl;

    return 0;
}
