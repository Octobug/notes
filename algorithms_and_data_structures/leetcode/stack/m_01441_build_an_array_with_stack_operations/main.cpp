#include <iostream>
#include <stack>
#include <vector>
#include "array.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    vector<string> buildArray(vector<int> &target, int n)
    {
        string push = "Push", pop = "Pop";
        stack<int> stk;
        vector<string> result;
        int matchIndex = 0;

        for (int i = 1; i <= n; i++)
        {
            stk.push(i);
            result.push_back(push);

            if (i == target[matchIndex])
            {
                matchIndex++;
            }
            else
            {
                stk.pop();
                result.push_back(pop);
            }

            if (matchIndex >= target.size())
                break;
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> targets = {
        {1, 3},    // ["Push","Push","Pop","Push"]
        {1, 2, 3}, // ["Push","Push","Push"]
        {1, 2},    // ["Push","Push"]
    };
    vector<int> ns = {
        3,
        3,
        4,
    };

    int group = getGroup();
    Solution s;

    vector<string> result = s.buildArray(targets[group], ns[group]);
    output(result);

    return 0;
}
