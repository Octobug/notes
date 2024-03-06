#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    string maximumOddBinaryNumber(string s)
    {
        int count1 = -1, len = s.size();

        for (int i = 0; i < len; i++)
        {
            if (s[i] == '1')
                count1++;
        }

        for (int i = 0; i < count1; i++)
        {
            s[i] = '1';
        }

        for (int i = count1; i < len - 1; i++)
        {
            s[i] = '0';
        }

        s[len - 1] = '1';

        return s;
    }
};

int main()
{
    vector<string> ss = {
        "010",  // 001
        "0101", // 1001
        "10",   // 01
    };
    int group = getGroup();

    Solution s;
    cout << s.maximumOddBinaryNumber(ss[group]) << endl;

    return 0;
}
