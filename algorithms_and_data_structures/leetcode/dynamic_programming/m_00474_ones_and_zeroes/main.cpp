#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int findMaxForm(vector<string> &strs, int m, int n)
    {
        int count01[strs.size()][2];
        for (int i = 0; i < strs.size(); i++)
        {
            count01[i][0] = 0;
            count01[i][1] = 0;
            for (int j = 0; j < strs[i].size(); j++)
                count01[i][strs[i][j] - '0']++;
        }

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < strs.size(); i++)
        {
            for (int j = m; j >= count01[i][0]; j--)
            {
                for (int k = n; k >= count01[i][1]; k--)
                {
                    dp[j][k] = max(
                        dp[j][k],
                        dp[j - count01[i][0]][k - count01[i][1]] + 1);
                }
            }
        }

        return dp[m][n];
    }
};

int main()
{
    vector<vector<string>> strs = {
        {"10", "0001", "111001", "1", "0"},
        {"10", "0", "1"},
    };
    vector<vector<int>> mns = {
        {5, 3},
        {1, 1},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.findMaxForm(strs[group], mns[group][0], mns[group][1]) << endl;

    return 0;
}
