#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int minPairSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());

        int result = 0;
        int begin = 0, end = nums.size() - 1;

        while (begin < end)
            result = max(result, nums[begin++] + nums[end--]);

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {3, 5, 2, 3},                   // 7
        {3, 5, 4, 2, 4, 6},             // 8
        {4, 1, 5, 1, 2, 5, 1, 5, 5, 4}, // 8
    };
    int group = getGroup();

    Solution s;
    cout << s.minPairSum(nums[group]) << endl;

    return 0;
}
