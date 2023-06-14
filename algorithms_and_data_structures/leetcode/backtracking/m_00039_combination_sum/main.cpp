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
            backtrack(candidates, target, i);
            sum -= candidates[i];
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        sort(candidates.begin(), candidates.end());
        backtrack(candidates, target, 0);
        return result;
    }
};

int main()
{
    vector<vector<vector<int>>> inputs = {
        {{2, 3, 6, 7}, {7}},
        {{2, 3, 5}, {8}},
        {{2}, {1}},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    vector<vector<int>> result;
    Solution s;
    result = s.combinationSum(inputs[group][0], inputs[group][1][0]);
    output2d(result);

    return 0;
}
