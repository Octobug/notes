#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int maximumXOR(vector<int> &nums)
    {
        int result = nums[0];

        for (int i = 1; i < nums.size(); i++)
            result |= nums[i];

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {3, 2, 4, 6},    // 7
        {1, 2, 3, 9, 2}, // 11
    };
    int group = getGroup();

    Solution s;
    cout << s.maximumXOR(nums[group]) << endl;

    return 0;
}
