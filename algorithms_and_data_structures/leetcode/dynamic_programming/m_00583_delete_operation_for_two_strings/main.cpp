#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int len1 = word1.size(), len2 = word2.size();

        int dp[len1 + 1][len2 + 1];

        for (int i = 0; i <= len2; i++)
            dp[0][i] = i;

        for (int i = 1; i <= len1; i++)
        {
            dp[i][0] = dp[i - 1][0] + 1;
            for (int j = 1; j <= len2; j++)
            {
                if (word1[i - 1] == word2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1;
            }
        }

        return dp[len1][len2];
    }
};

int main()
{
    vector<string> w1s = {
        "sea",      // 2
        "leetcode", // 4
        "kitten",   // 5
        "food",     // 7
    };
    vector<string> w2s = {
        "eat",
        "etco",
        "sitting",
        "money",
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.minDistance(w1s[group], w2s[group]) << endl;

    return 0;
}
