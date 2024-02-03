#include <iostream>
#include <vector>
#include "input.h"
#include "array.h"

using namespace std;

class Solution
{
public:
    string sortVowels(string s)
    {
        int count[128] = {0};
        bool isVowel[128] = {false};

        string vowels = "AEIOUaeiou";
        for (int i = 0; i < vowels.size(); i++)
            isVowel[vowels[i]] = true;

        for (int i = 0; i < s.size(); i++)
        {
            if (isVowel[s[i]])
                count[s[i]]++;
        }

        int vidx = 0;
        for (int i = 0; i < s.size(); i++)
        {
            while (vidx < vowels.size() && count[vowels[vidx]] == 0)
                vidx++;

            if (isVowel[s[i]])
            {
                s[i] = vowels[vidx];
                count[vowels[vidx]]--;
            }
        }

        return s;
    }
};

int main()
{
    vector<string> ss = {
        "lEetcOde", // lEOtcede
        "lYmpH",    // lYmpH
    };
    int group = getGroup();

    Solution s;
    cout << s.sortVowels(ss[group]) << endl;

    return 0;
}
