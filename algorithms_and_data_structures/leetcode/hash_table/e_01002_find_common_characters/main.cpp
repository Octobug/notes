#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<string> commonChars(vector<string> &words)
    {
        int total[26] = {0};
        for (int i = 0; i < words[0].size(); i++)
            total[words[0][i] - 'a']++;

        for (int i = 1; i < words.size(); i++)
        {
            int cur[26] = {0};
            for (int j = 0; j < words[i].size(); j++)
                cur[words[i][j] - 'a']++;

            for (int k = 0; k < 26; k++)
                total[k] = min(total[k], cur[k]);
        }

        vector<string> result;
        for (int i = 0; i < 26; i++)
        {
            for (int j = 0; j < total[i]; j++)
            {
                string ch = {char('a' + i)};
                result.push_back(ch);
            }
        }

        return result;
    }
};

int main()
{
    vector<vector<string>> words = {
        {"bella", "label", "roller"}, // "e","l","l"
        {"cool", "lock", "cook"},     // "c","o"
        {"cbabdbdd", "dabadcac", "dabbdaac", "badaccab", "cbadacad",
         "ccccbbaa", "cbcbdaba", "bdadcbdd"}, // "a","b","c"
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<string> result = s.commonChars(words[group]);
    output(result);

    return 0;
}
