#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    int search(vector<int> &nums, int target)
    {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right)
        {
            int mid = left + ((right - left) / 2); // 防止溢出
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
        return -1;
    }
};

int main()
{
    Solution s;

    vector<int> nums = {-1, 0, 3, 5, 9, 12, 15};
    int target1 = 9;
    int target2 = 2;

    int index = s.search(nums, target1);

    cout << index << endl;
}
