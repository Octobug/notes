#include <algorithm>
#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<vector<int>> result;
    vector<int> path;
    int sum = 0;

    void backtrack(vector<int> &candidates, int target, int start)
    {
        if (sum == target)
        {
            result.push_back(path);
            return;
        }

        for (int i = start; i < candidates.size(); i++)
        {
            if (sum + candidates[i] > target)
                break;

            path.push_back(candidates[i]);
            sum += candidates[i];

            backtrack(candidates, target, i + 1);
            sum -= candidates[i];
            path.pop_back();

            while (i < candidates.size() - 1 && candidates[i] == candidates[i + 1])
                i++;
        }
    }

    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        sort(candidates.begin(), candidates.end());
        backtrack(candidates, target, 0);
        return result;
    }
};

int main()
{
    vector<vector<vector<int>>> inputs = {
        {{10, 1, 2, 7, 6, 1, 5}, {8}},
        {{2, 5, 2, 1, 2}, {5}},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    vector<vector<int>> result;
    Solution s;
    result = s.combinationSum2(inputs[group][0], inputs[group][1][0]);
    output2d(result);

    return 0;
}
