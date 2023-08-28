#include <iostream>
#include <vector>
#include <string>

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
                {
                    left--;
                }
                while (right < nums.size() && nums[mid] == nums[right])
                {
                    right++;
                }
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
    Solution s;

    vector<int> nums1 = {5, 7, 7, 8, 8, 10};
    vector<int> nums2 = {1};
    int target;

    cout << "Please input target: ";
    cin >> target;

    vector<int> range = s.searchRange(nums2, target);

    cout << range[0] << ", " << range[1] << endl;
}
