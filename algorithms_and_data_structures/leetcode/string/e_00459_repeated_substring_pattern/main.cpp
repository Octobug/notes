#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    bool repeatedSubstringPattern(string s)
    {
        int len = s.size();
        if (len < 2)
        {
            return false;
        }

        int next[len];
        getNextMax(next, s);

        if (next[len - 1] != 0 && len % (len - next[len - 1]) == 0)
        {
            return true;
        }
        return false;
    }

    void getNextMax(int next[], string &s)
    {
        int j = 0;
        next[0] = 0;

        for (int i = 1; i < s.size(); i++)
        {
            while (j > 0 && s[i] != s[j])
            {
                j = next[j - 1];
            }
            if (s[i] == s[j])
            {
                j++;
            }
            next[i] = j;
        }
    }
};

int main()
{
    vector<string> groups = {
        "abab",
        "aba",
        "abcabcabcabc",
        "abac",
        "a",
        "ababac",
    };

    int group;
    cout << "Please input group: ";
    cin >> group;

    Solution s;
    cout << s.repeatedSubstringPattern(groups[group - 1]) << endl;

    return 0;
}
