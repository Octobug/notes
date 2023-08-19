#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class SolutionDP
{
public:
    int countSubstrings(string s)
    {
        int len = s.size();
        bool dp[len + 1][len + 1];

        for (int i = 0; i <= len; i++)
            for (int j = 0; j <= len; j++)
                dp[i][j] = true;

        int result = len;
        for (int i = 2; i <= len; i++)
        {
            for (int j = i; j <= len; j++)
            {
                if (s[j - 1] == s[j - i] && dp[i - 2][j - 1])
                    result++;
                else
                    dp[i][j] = false;
            }
        }

        return result;
    }
};

class Solution
{
public:
    int countSubstrings(string s)
    {
        int result = 0;
        for (int i = 0; i < s.size(); i++)
        {
            result += extend(s, i, i, s.size());     // 以i为中心
            result += extend(s, i, i + 1, s.size()); // 以i和i+1为中心
        }
        return result;
    }
    int extend(const string &s, int i, int j, int n)
    {
        int res = 0;
        while (i >= 0 && j < n && s[i] == s[j])
        {
            i--;
            j++;
            res++;
        }
        return res;
    }
};

int main()
{
    vector<string> ss = {
        "aa",     // 3
        "ab",     // 2
        "abc",    // 3
        "aaa",    // 6
        "aba",    // 4
        "abba",   // 6
        "fdsklf", // 6
        "aaaaa",  //
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.countSubstrings(ss[group]) << endl;

    return 0;
}
