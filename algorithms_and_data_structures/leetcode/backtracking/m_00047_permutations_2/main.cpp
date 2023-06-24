#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
    vector<vector<int>> result;
    vector<int> permuts;
    bool usedIndex[8] = {false};

public:
    void backtrack(vector<int> &nums)
    {
        if (permuts.size() == nums.size())
        {
            result.push_back(permuts);
            return;
        }

        bool usedNums[21] = {false};
        for (int i = 0; i < nums.size(); i++)
        {
            if (usedIndex[i])
                continue;

            if (usedNums[nums[i] + 10])
                continue;

            usedIndex[i] = true;
            usedNums[nums[i] + 10] = true;
            permuts.push_back(nums[i]);

            backtrack(nums);

            usedIndex[i] = false;
            permuts.pop_back();
        }
    }

    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        backtrack(nums);
        return result;
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {1, 1, 2},
        {1, 2, 3},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<int>> result = s.permuteUnique(inputs[group]);
    output2d(result);

    return 0;
}
