#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        int result = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            result = result xor nums[i];
        }
        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {2, 2, 1},       // 1
        {4, 1, 2, 1, 2}, // 4
        {1}              // 1
    };
    int group = getGroup();
    Solution s;
    cout << s.singleNumber(nums[group]) << endl;

    return 0;
}
