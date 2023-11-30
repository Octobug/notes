#include <iostream>
#include <vector>
#include "array.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    vector<int> findWordsContaining(vector<string> &words, char x)
    {
        vector<int> result(words.size(), 0);
        int index = 0;

        for (int i = 0; i < words.size(); i++)
        {
            if (words[i].find(x) != string::npos)
                result[index++] = i;
        }

        result.resize(index);
        return result;
    }
};

int main()
{
    vector<vector<string>> words = {
        {"leet", "code"},              // [0,1]
        {"abc", "bcd", "aaaa", "cbc"}, // 0,2
        {"abc", "bcd", "aaaa", "cbc"}, // []
    };
    vector<char> xs = {'e', 'a', 'z'};

    int group = getGroup();
    Solution s;
    vector<int> result = s.findWordsContaining(words[group], xs[group]);
    output(result);

    return 0;
}
