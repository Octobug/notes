#include <iostream>
#include <vector>
#include "array.h"

class Solution
{
    vector<vector<int>> result;
    vector<int> subset;

public:
    void backtrack(vector<int> &nums, int begin)
    {
        result.push_back(subset);
        for (int i = begin; i < nums.size(); i++)
        {
            subset.push_back(nums[i]);
            backtrack(nums, i + 1);
            subset.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int> &nums)
    {
        backtrack(nums, 0);
        return result;
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {1, 2, 3},
        {0},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<int>> result = s.subsets(inputs[group]);
    output2d(result);

    return 0;
}
