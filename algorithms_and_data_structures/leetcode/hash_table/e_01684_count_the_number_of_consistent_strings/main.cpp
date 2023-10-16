#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int countConsistentStrings(string allowed, vector<string> &words)
    {
        bool table[26] = {false};

        for (int i = 0; i < allowed.size(); i++)
            table[allowed[i] - 'a'] = true;

        int result = 0;
        for (int i = 0; i < words.size(); i++)
        {
            bool consistent = true;
            for (int j = 0; j < words[i].size(); j++)
            {
                if (!table[words[i][j] - 'a'])
                {
                    consistent = false;
                    break;
                }
            }
            if (consistent)
                result++;
        }

        return result;
    }
};

int main()
{
    vector<string> alloweds = {
        "ab",  // 2
        "abc", // 7
        "cad", // 4
    };

    vector<vector<string>> words = {
        {"ad", "bd", "aaab", "baa", "badab"},
        {"a", "b", "c", "ab", "ac", "bc", "abc"},
        {"cc", "acd", "b", "ba", "bac", "bad", "ac", "d"},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.countConsistentStrings(alloweds[group], words[group]) << endl;

    return 0;
}
