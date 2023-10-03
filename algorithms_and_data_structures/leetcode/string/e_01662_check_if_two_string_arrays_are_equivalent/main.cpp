#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    bool arrayStringsAreEqual(vector<string> &word1, vector<string> &word2)
    {
        int i1 = 0, j1 = 0, wlen1 = word1[0].size();
        int i2 = 0, j2 = 0, wlen2 = word2[0].size();
        bool end1 = false;
        bool end2 = false;

        while (j1 < wlen1 && j2 < wlen2)
        {
            if (word1[i1][j1] != word2[i2][j2])
                return false;

            j1++;
            j2++;

            if (j1 >= wlen1)
            {
                i1++;

                if (i1 >= word1.size())
                    end1 = true;
                else
                {
                    j1 = 0;
                    wlen1 = word1[i1].size();
                }
            }
            if (j2 >= wlen2)
            {
                i2++;
                if (i2 >= word2.size())
                    end2 = true;
                else
                {
                    j2 = 0;
                    wlen2 = word2[i2].size();
                }
            }
        }

        return end1 && end2;
    }
};

int main()
{
    vector<vector<string>> word1s = {
        {"ab", "c"},          // 1
        {"a", "cb"},          // 0
        {"abc", "d", "defg"}, // 1
        {"abc", "d", "defg"}, // 0
    };
    vector<vector<string>> word2s = {
        {"a", "bc"},
        {"ab", "c"},
        {"abcddefg"},
        {"abcddef"},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.arrayStringsAreEqual(word1s[group], word2s[group]) << endl;

    return 0;
}
