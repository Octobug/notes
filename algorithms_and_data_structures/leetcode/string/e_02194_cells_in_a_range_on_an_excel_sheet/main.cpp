#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<string> cellsInRange(string s)
    {
        char charBegin = s[0], charEnd = s[3];
        char numBegin = s[1], numEnd = s[4];
        int rowLen = numEnd - numBegin + 1;
        int colLen = charEnd - charBegin + 1;

        vector<string> result(rowLen * colLen, "00");

        int index = 0;
        for (char c = charBegin; c <= charEnd; c++)
        {
            for (char n = numBegin; n <= numEnd; n++)
            {
                result[index][0] = c;
                result[index][1] = n;
                index++;
            }
        }

        return result;
    }
};

int main()
{
    vector<string> ss = {
        "K1:L2", // ["K1","K2","L1","L2"]
        "A1:F1", // ["A1","B1","C1","D1","E1","F1"]
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<string> result = s.cellsInRange(ss[group]);
    output(result);

    return 0;
}
