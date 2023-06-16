#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
    vector<vector<string>> result;
    vector<string> path;

public:
    bool isPalindrome(string &s, int begin, int len)
    {
        if (len == 1)
            return true;

        int end = begin + len - 1;
        while (begin <= end)
            if (s[begin++] != s[end--])
                return false;

        return true;
    }

    void backtrack(string &s, int begin)
    {
        if (begin >= s.size())
        {
            result.push_back(path);
            return;
        }

        int substrSize = s.size() - begin;
        for (int len = 1; len <= substrSize; len++)
        {
            if (isPalindrome(s, begin, len))
                path.push_back(s.substr(begin, len));
            else
                continue;

            backtrack(s, begin + len);

            path.pop_back();
        }
    }

    vector<vector<string>> partition(string s)
    {
        result.clear();
        path.clear();
        backtrack(s, 0);
        return result;
    }
};

int main()
{
    vector<string> inputs = {
        "aab",
        "a",
        "abbab",
        "aabb",
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<string>> result = s.partition(inputs[group]);
    output2d(result);

    return 0;
}
