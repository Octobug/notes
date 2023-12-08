#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    string mergeAlternately(string word1, string word2)
    {
        int len1 = word1.size();
        int len2 = word2.size();
        string result(len1 + len2, ' ');

        int i1 = 0, i2 = 0, i = 0;
        while (i1 < len1 && i2 < len2)
        {
            result[i++] = word1[i1++];
            result[i++] = word2[i2++];
        }

        while (i1 < len1)
            result[i++] = word1[i1++];
        while (i2 < len2)
            result[i++] = word2[i2++];

        return result;
    }
};

int main()
{
    vector<vector<string>> words = {
        {"abc", "pqr"}, // "apbqcr"
        {"ab", "pqrs"}, // "apbqrs"
        {"abcd", "pq"}, // "apbqcd"
    };

    int group = getGroup();

    Solution s;
    cout << s.mergeAlternately(words[group][0], words[group][1]) << endl;

    return 0;
}
