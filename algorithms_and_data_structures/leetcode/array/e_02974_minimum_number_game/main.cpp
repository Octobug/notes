#include <iostream>
#include <vector>
#include "array.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    vector<int> numberGame(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());

        int left = 0, right = 1;

        while (right < nums.size())
        {
            swap(nums[left], nums[right]);
            left += 2;
            right += 2;
        }

        return nums;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {5, 4, 2, 3}, // [3,2,5,4]
        {2, 5},       // [5,2]
    };

    int group = getGroup();

    Solution s;
    vector<int> result = s.numberGame(nums[group]);
    output(result);
}
