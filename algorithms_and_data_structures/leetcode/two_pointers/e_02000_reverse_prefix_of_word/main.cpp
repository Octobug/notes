#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    string reversePrefix(string word, char ch)
    {
        int begin = 0, end = 0;
        for (; end < word.size(); end++)
        {
            if (word[end] == ch)
                break;
        }

        if (end < word.size())
        {
            while (begin < end)
            {
                swap(word[begin], word[end]);
                begin++;
                end--;
            }
        }

        return word;
    }
};

int main()
{
    vector<string> words = {
        "abcdefd", // "dcbaefd"
        "xyxzxe",  // "zxyxxe"
        "abcd",    // "abcd"
    };
    vector<char> chs = {
        'd',
        'z',
        'z',
    };

    int group = getGroup();
    Solution s;
    cout << s.reversePrefix(words[group], chs[group]) << endl;

    return 0;
}
