#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
private:
    vector<vector<string>> result;
    vector<string> path;
    vector<vector<bool>> dp;

    void backtrack(const string &s, int startIndex)
    {
        if (startIndex >= s.size())
        {
            result.push_back(path);
            return;
        }

        for (int i = startIndex; i < s.size(); i++)
        {
            if (!dp[startIndex][i])
                continue;

            string str = s.substr(startIndex, i - startIndex + 1);
            path.push_back(str);

            backtrack(s, i + 1);

            path.pop_back();
        }
    }

    void computePalindrome(const string &s)
    {
        // dp[i][j] 代表 s[i:j] 是否是回文字串
        dp.resize(s.size(), vector<bool>(s.size(), false));

        for (int i = s.size() - 1; i >= 0; i--)
        {
            for (int j = i; j < s.size(); j++)
            {
                if (j == i)
                    dp[i][j] = true;
                else if (j - i == 1)
                    dp[i][j] = (s[i] == s[j]);
                else
                    dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);
            }
        }
    }

public:
    vector<vector<string>> partition(string s)
    {
        result.clear();
        path.clear();
        computePalindrome(s);
        backtrack(s, 0);
        return result;
    }
};

int main()
{
    vector<string> inputs = {
        "aab",
        "a",
        "abbab",
        "aabb",
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<string>> result = s.partition(inputs[group]);
    output2d(result);

    return 0;
}
