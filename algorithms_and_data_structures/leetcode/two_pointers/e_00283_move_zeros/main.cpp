#include <iostream>
#include <vector>
#include <string>

#include "array.h"

using namespace std;

class Solution
{
public:
    void moveZeroes(vector<int> &nums)
    {
        int slow = 0;
        for (int fast = 1; fast < nums.size(); fast++)
        {
            if (nums[slow] != 0)
            {
                slow++;
            }
            else if (nums[fast] != 0)
            {
                nums[slow++] = nums[fast];
                nums[fast] = 0;
            }
        }
    }
};

int main()
{
    vector<vector<int>> nums = {
        {0, 1, 0, 3, 12}, // 1,3,12,0,0
        {0},              // 0
        {1, 0, 1},        // 1,1,0
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    s.moveZeroes(nums[group]);

    output(nums[group]);
}
