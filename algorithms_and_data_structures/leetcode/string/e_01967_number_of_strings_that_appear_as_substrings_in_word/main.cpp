#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int numOfStrings(vector<string> &patterns, string word)
    {
        int result = 0;

        for (int i = 0; i < patterns.size(); i++)
        {
            if (word.find(patterns[i]) != string::npos)
                result++;
        }

        return result;
    }
};

int main()
{
    vector<vector<string>> patterns = {
        {"a", "abc", "bc", "d"}, // 3
        {"a", "b", "c"},         // 2
    };
    vector<string> words = {
        "abc",
        "aaaaabbbbb",
    };

    int group = getGroup();
    Solution s;
    cout << s.numOfStrings(patterns[group], words[group]) << endl;

    return 0;
}
