#include <cctype>
#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int countKeyChanges(string s)
    {
        int result = 0;
        char last = tolower(s[0]);

        for (int i = 1; i < s.size(); i++)
        {
            if (tolower(s[i]) != last)
            {
                result++;
                last = tolower(s[i]);
            }
        }
        return result;
    }
};

int main()
{
    vector<string> ss = {
        "aAbBcC",   // 2
        "AaAaAaaA", // 0
    };

    int group = getGroup();
    Solution s;
    cout << s.countKeyChanges(ss[group]) << endl;

    return 0;
}
