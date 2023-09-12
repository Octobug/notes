#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class SolutionOrigin
{
public:
    int minCut(string s)
    {
        int len = s.size();
        bool palin[len + 1][len];

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < len; j++)
                palin[i][j] = true;

        for (int i = 2; i <= len; i++)
            for (int j = 0; j <= len - i; j++)
                if (s[j] == s[j + i - 1])
                    palin[i][j] = palin[i - 2][j + 1];
                else
                    palin[i][j] = false;

        int dp[len];
        for (int i = 0; i < len; i++)
            dp[i] = i;

        for (int i = 1; i < len; i++)
        {
            if (palin[i + 1][0])
            {
                dp[i] = 0;
                continue;
            }

            for (int j = 0; j < i; j++)
                if (palin[i - j][j + 1])
                    dp[i] = min(dp[i], dp[j] + 1);
        }

        return dp[len - 1];
    }
};

class Solution
{
public:
    int minCut(string s)
    {
        vector<vector<bool>> isPalin(s.size(), vector<bool>(s.size(), false));
        for (int i = s.size() - 1; i >= 0; i--)
            for (int j = i; j < s.size(); j++)
                if (s[i] == s[j] && (j - i <= 1 || isPalin[i + 1][j - 1]))
                    isPalin[i][j] = true;

        vector<int> dp(s.size(), 0);
        for (int i = 0; i < s.size(); i++)
            dp[i] = i;

        for (int i = 1; i < s.size(); i++)
        {
            if (isPalin[0][i])
            {
                dp[i] = 0;
                continue;
            }
            for (int j = 0; j < i; j++)
                if (isPalin[j + 1][i])
                    dp[i] = min(dp[i], dp[j] + 1);
        }
        return dp[s.size() - 1];
    }
};

int main()
{
    vector<string> ss = {
        "aab",          // 1
        "a",            // 0
        "ab",           // 1
        "cabababcbc",   // 3
        "ababbbabbaba", // 3
        "bb",           // 0
        "aabc",         // 2
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.minCut(ss[group]) << endl;

    return 0;
}
