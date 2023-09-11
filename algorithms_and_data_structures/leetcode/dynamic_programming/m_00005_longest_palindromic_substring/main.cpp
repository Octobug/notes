#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class SolutionDP
{
public:
    string longestPalindrome(string s)
    {
        int len = s.size();
        bool dp[2][len + 1];

        for (int i = 0; i <= 1; i++)
            for (int j = 1; j <= len; j++)
                dp[i][j] = true;

        int subIndex = 0;
        int maxLen = 1;
        int row;
        for (int i = 2; i <= len; i++)
        {
            row = i % 2;
            for (int j = len; j >= i; j--)
            {
                if (s[j - 1] == s[j - i])
                {
                    dp[row][j] = dp[row][j - 1];
                    if (dp[row][j])
                    {
                        maxLen = i;
                        subIndex = j - i;
                    }
                }
                else
                    dp[row][j] = false;
            }

            if (i - maxLen >= 2)
                break;
        }

        return s.substr(subIndex, maxLen);
    }
};

class Solution
{
public:
    int subIndex = 0;
    int maxLength = 0;

    string longestPalindrome(string s)
    {
        int len = s.size();
        for (int i = 0; i < len; i++)
        {
            extend(s, i, i, len);
            extend(s, i, i + 1, len);
        }
        return s.substr(subIndex, maxLength);
    }

    void extend(const string &s, int i, int j, int n)
    {
        while (i >= 0 && j < n && s[i] == s[j])
        {
            if (j - i + 1 > maxLength)
            {
                subIndex = i;
                maxLength = j - i + 1;
            }
            i--;
            j++;
        }
    }
};

int main()
{
    vector<string> ss = {
        "babad",       // bab
        "cbbd",        // bb
        "abcba",       // abcba
        "aacabdkacaa", // aca
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.longestPalindrome(ss[group]) << endl;

    return 0;
}
