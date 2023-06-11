#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
    vector<vector<int>> result;
    vector<int> path;

    void backtrack(int n, int k, int start)
    {
        if (path.size() == k)
        {
            result.push_back(path);
            return;
        }

        for (int i = start; i <= (n - (k - path.size()) + 1); i++)
        {
            path.push_back(i);
            backtrack(n, k, i + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combine(int n, int k)
    {
        backtrack(n, k, 1);
        return result;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {4, 2},
        {1, 1},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<int>> result = s.combine(groups[group][0], groups[group][1]);
    output2d(result);

    return 0;
}
