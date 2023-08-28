#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> searchRange(vector<int> &nums, int target)
    {
        int left = 0;
        int right = nums.size() - 1;
        int mid;
        while (left <= right)
        {
            mid = left + ((right - left) / 2); // 防止溢出
            if (target == nums[mid])
            {
                left = mid;
                right = mid;
                while (left >= 0 && nums[mid] == nums[left])
                    left--;

                while (right < nums.size() && nums[mid] == nums[right])
                    right++;

                return {left + 1, right - 1};
            }
            else if (target > nums[mid])
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        return {-1, -1};
    }
};

int main()
{
    vector<vector<int>> nums = {
        {5, 7, 7, 8, 8, 10}, // 3,4
        {5, 7, 7, 8, 8, 10}, // -1,-1
        {},                  // -1,-1
    };
    vector<int> targets = {8, 6, 0};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<int> result = s.searchRange(nums[group], targets[group]);
    output(result);
}
