#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int scoreOfString(string s)
    {
        int result = 0;
        for (int i = 1; i < s.size(); i++)
        {
            result += abs(s[i] - s[i - 1]);
        }
        return result;
    }
};

int main()
{
    vector<string> ss = {
        "hello",
        "zaz",
    };
    int group = getGroup();

    Solution s;
    cout << s.scoreOfString(ss[group]) << endl;

    return 0;
}
