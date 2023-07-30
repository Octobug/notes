#include <iostream>
#include <unordered_set>
#include <vector>
#include "array.h"

using namespace std;

class SolutionWorse
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;

        for (int i = 1; i <= s.size(); i++) // 遍历背包
        {
            for (int j = 0; j < i; j++)
            {
                string word = s.substr(j, i - j);
                if (wordSet.count(word) && dp[j])
                    dp[i] = true;
            }
        }
        return dp[s.size()];
    }
};

class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;

        for (int i = 1; i <= s.size(); i++)
        {
            for (int j = 0; j < wordDict.size(); j++)
            {
                if (i >= wordDict[j].size())
                {
                    string word = s.substr(i - wordDict[j].size(), wordDict[j].size());
                    if (word == wordDict[j] && dp[i - wordDict[j].size()])
                        dp[i] = true;
                }
            }
        }

        return dp[s.size()];
    }
};

class SolutionWrong
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        vector<int> dp(s.size() + 1, false);
        dp[0] = true;

        for (int i = 0; i < wordDict.size(); i++) // 遍历物品
        {
            for (int j = wordDict[i].size(); j <= s.size(); j++) // 遍历背包
            {
                // 这其实是个背包排列问题：
                //  后面可能还有物品需要被再次使用，而先遍历物品导致物品的使用是有顺序的
                //  因此不能确保后续物品可被再次使用
                string word = s.substr(j - wordDict[i].size(), wordDict[i].size());
                if (word == wordDict[i] && dp[j - wordDict[i].size()])
                    dp[j] = true;

                output(dp);
            }
        }

        return dp[s.size()];
    }
};

int main()
{
    vector<string> ss = {
        "leetcode",
        "applepenapple",
        "catsandog",
    };
    vector<vector<string>> wordDicts = {
        {"leet", "code"},
        {"apple", "pen"},
        {"cats", "dog", "sand", "and", "cat"},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.wordBreak(ss[group], wordDicts[group]) << endl;

    return 0;
}
