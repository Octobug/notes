#include <iostream>
#include <vector>
#include <unordered_set>
#include "array.h"

using namespace std;

class Solution
{
    vector<vector<int>> result;
    vector<int> seq;

public:
    void backtrack(vector<int> &nums, int begin)
    {
        if (seq.size() >= 2)
            result.push_back(seq);

        unordered_set<int> numset;

        for (int i = begin; i < nums.size(); i++)
        {
            if (!seq.empty() && nums[i] < seq.back())
                continue;
            if (numset.find(nums[i]) != numset.end())
                continue;

            numset.insert(nums[i]);

            seq.push_back(nums[i]);
            backtrack(nums, i + 1);
            seq.pop_back();
        }
    }

    vector<vector<int>> findSubsequences(vector<int> &nums)
    {
        backtrack(nums, 0);
        return result;
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {4, 6, 7, 7},
        {4, 4, 3, 2, 1},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1, 1, 1},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<int>> result = s.findSubsequences(inputs[group]);
    output2d(result);

    return 0;
}
