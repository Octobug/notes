#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    int searchInsert(vector<int> &nums, int target)
    {
        int left = 0;
        int right = nums.size() - 1;
        int mid;
        while (left <= right)
        {
            mid = left + ((right - left) / 2); // 防止溢出
            if (target == nums[mid])
            {
                return mid;
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
        return left;
    }
};

int main()
{
    Solution s;

    vector<int> nums = {1, 3, 5, 6, 8, 11, 25};
    int target;

    cout << "Please input target: ";
    cin >> target;

    int index = s.searchInsert(nums, target);

    cout << index << endl;
}
