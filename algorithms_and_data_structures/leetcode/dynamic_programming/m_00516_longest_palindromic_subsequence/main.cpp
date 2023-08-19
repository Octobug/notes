#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int longestPalindromeSubseq(string s)
    {
        int len = s.size();
        int dp[len + 1][len + 1];

        for (int i = 0; i <= len; i++)
            for (int j = 0; j <= len; j++)
                dp[i][j] = 0;

        for (int i = 1; i <= len; i++)
            dp[1][i] = 1;

        for (int i = 2; i <= len; i++)
            for (int j = i; j <= len; j++)
            {
                if (s[j - 1] == s[j - i])
                    dp[i][j] = dp[i - 2][j - 1] + 2;
                else
                    dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]);
            }

        return dp[len][len];
    }
};

int main()
{
    vector<string> ss = {
        "bbbab", // 4
        "cbbd",  // 2
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.longestPalindromeSubseq(ss[group]) << endl;

    return 0;
}
