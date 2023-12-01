#include <iostream>
#include <vector>
#include "array.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    int minInsertions(string s)
    {
        int n = s.size();
        int dp[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dp[i][j] = 0;

        for (int i = 1; i < n; i++)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                if (s[i] == s[j])
                    dp[i][j] = dp[i - 1][j + 1];
                else
                    dp[i][j] = min(dp[i - 1][j], dp[i][j + 1]) + 1;
            }
        }

        return dp[n - 1][0];
    }
};

int main()
{
    vector<string> ss = {
        "zzazz",     // 0
        "mbadm",     // 2
        "leetcode",  // 5
        "zjveiiwvc", // 5
    };
    int group = getGroup();

    Solution s;
    cout << s.minInsertions(ss[group]) << endl;

    return 0;
}
