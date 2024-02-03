#include <iostream>
#include <vector>
#include "input.h"
#include "array.h"

using namespace std;

class Solution
{
public:
    int minSteps(string s, string t)
    {
        int table[26] = {0};

        for (int i = 0; i < s.size(); i++)
            table[s[i] - 'a']++;

        for (int i = 0; i < s.size(); i++)
            table[t[i] - 'a']--;

        int result = 0;
        for (int i = 0; i < 26; i++)
        {
            if (table[i] > 0)
                result += table[i];
        }

        return result;
    }
};

int main()
{
    vector<string> ss = {
        "bab",      // 1
        "leetcode", // 5
        "anagram",  // 0
    };
    vector<string> ts = {
        "aba",
        "practice",
        "mangaar",
    };

    int group = getGroup();
    Solution s;
    cout << s.minSteps(ss[group], ts[group]) << endl;

    return 0;
}
