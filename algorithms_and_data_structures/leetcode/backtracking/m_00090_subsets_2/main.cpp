#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

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
            while (i < nums.size() - 1 && nums[i + 1] == subset.back())
                i++;
            subset.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        backtrack(nums, 0);
        return result;
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {1, 2, 2},
        {0},
        {5, 5, 5, 5, 5},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<int>> result = s.subsetsWithDup(inputs[group]);
    output2d(result);

    return 0;
}
