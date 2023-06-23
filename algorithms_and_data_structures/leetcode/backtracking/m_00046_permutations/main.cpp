#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
    vector<vector<int>> result;
    vector<int> permuts;
    bool usedNums[21] = {false};

public:
    void backtrack(vector<int> &nums)
    {
        if (permuts.size() == nums.size())
        {
            result.push_back(permuts);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (usedNums[nums[i] + 10])
                continue;

            usedNums[nums[i] + 10] = true;
            permuts.push_back(nums[i]);

            backtrack(nums);

            usedNums[nums[i] + 10] = false;
            permuts.pop_back();
        }
    }

    vector<vector<int>> permute(vector<int> &nums)
    {
        backtrack(nums);
        return result;
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {1, 2, 3},
        {0, 1},
        {1},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<int>> result = s.permute(inputs[group]);
    output2d(result);

    return 0;
}
