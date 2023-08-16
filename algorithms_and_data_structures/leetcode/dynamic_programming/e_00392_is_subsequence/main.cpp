#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution2D
{
public:
    bool isSubsequence(string s, string t)
    {
        int lens = s.size(), lent = t.size();

        vector<vector<int>> dp(lens + 1, vector<int>(lent + 1, 0));

        for (int i = 0; i < lens; i++)
        {
            for (int j = 0; j < lent; j++)
            {
                if (s[i] == t[j])
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                else
                    dp[i + 1][j + 1] = dp[i + 1][j];
            }
        }

        return dp[lens][lent] == lens;
    }
};

class Solution
{
public:
    bool isSubsequence(string s, string t)
    {
        int lens = s.size(), lent = t.size();
        int si = 0, ti = 0;

        while (si < lens && ti < lent)
        {
            if (s[si] == t[ti])
                si++;
            ti++;
        }

        return si == lens;
    }
};

int main()
{
    vector<string> ss = {
        "abc",    // true
        "axc",    // false
        "aaaaaa", // false
    };

    vector<string> tt = {
        "ahbgdc",
        "ahbgdc",
        "bbaaaa",
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.isSubsequence(ss[group], tt[group]) << endl;

    return 0;
}
