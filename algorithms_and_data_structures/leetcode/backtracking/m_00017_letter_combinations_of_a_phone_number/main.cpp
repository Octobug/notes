#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
    vector<string> result;
    string path = "";
    const string letterMap[10] = {
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz", // 9
    };

public:
    void backtrack(string &digits, int digitsIdx)
    {
        if (digitsIdx == digits.size())
        {
            result.push_back(path);
            return;
        }

        int digit = digits[digitsIdx] - '0';
        int letterSize = letterMap[digit].size();

        for (int i = 0; i < letterSize; i++)
        {
            path.push_back(letterMap[digit][i]);
            backtrack(digits, digitsIdx + 1);
            path.pop_back();
        }
    }

    vector<string> letterCombinations(string digits)
    {
        if (digits.empty())
            return result;

        backtrack(digits, 0);
        return result;
    }
};

int main()
{
    vector<string> inputs = {
        "23",
        "",
        "2",
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<string> result = s.letterCombinations(inputs[group]);
    output<string>(result);

    return 0;
}
