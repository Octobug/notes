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
    Solution s;

    vector<int> nums1 = {0, 1, 0, 3, 12};
    vector<int> nums2 = {0};
    vector<int> nums3 = {1, 0, 1};

    vector<vector<int>> groups = {nums1, nums2, nums3};

    int group;

    cout << "Please input group: ";
    cin >> group;

    s.moveZeroes(groups[group - 1]);

    output(groups[group - 1]);
}
