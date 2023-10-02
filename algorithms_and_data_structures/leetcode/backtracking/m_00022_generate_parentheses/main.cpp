#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<string> result;
    string path;
    int pathIdx = 0;

    void backtrack(int left, int right)
    {
        if (right < left)
            return;
        if (left <= 0 && right <= 0)
        {
            result.push_back(path);
            return;
        }

        if (left > 0)
        {
            path[pathIdx++] = '(';
            backtrack(left - 1, right);
            pathIdx--;
        }
        path[pathIdx++] = ')';
        backtrack(left, right - 1);
        pathIdx--;
    }

    vector<string> generateParenthesis(int n)
    {
        path = string(n * 2, '-');
        backtrack(n, n);
        return result;
    }
};

int main()
{
    int n;
    cout << "Please input n: ";
    cin >> n;

    Solution s;
    vector<string> result = s.generateParenthesis(n);
    output(result);

    return 0;
}
