#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    string freqAlphabets(string s)
    {
        int numOfLetter = 0;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            if (s[i] == '#')
                i -= 2;

            numOfLetter++;
        }

        string result(numOfLetter, ' ');
        for (int i = s.size() - 1, j = numOfLetter - 1; i >= 0; i--, j--)
        {
            if (s[i] == '#')
            {
                result[j] = 'a' + ((s[i - 2] - '0') * 10 + (s[i - 1] - '1'));
                i -= 2;
            }
            else
            {
                result[j] = s[i] - '1' + 'a';
            }
        }

        return result;
    }
};

int main()
{
    vector<string> ss = {
        "10#11#12", // "jkab"
        "1326#",    // "acz"
    };

    int group = getGroup();
    Solution s;
    cout << s.freqAlphabets(ss[group]) << endl;

    return 0;
}
