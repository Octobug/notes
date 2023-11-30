#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    string firstPalindrome(vector<string> &words)
    {
        for (int i = 0; i < words.size(); i++)
        {
            int begin = 0, end = words[i].size() - 1;
            while (begin < end)
            {
                if (words[i][begin] != words[i][end])
                    break;

                begin++;
                end--;
            }

            if (begin >= end)
                return words[i];
        }

        return "";
    }
};

int main()
{
    vector<vector<string>> words = {
        {"abc", "car", "ada", "racecar", "cool"}, // "ada"
        {"notapalindrome", "racecar"},            // "racecar"
        {"def", "ghi"},                           // ""
    };

    int group = getGroup();
    Solution s;
    cout << s.firstPalindrome(words[group]) << endl;

    return 0;
}
