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
                return mid;
            else if (target > nums[mid])
                left = mid + 1;
            else
                right = mid - 1;
        }
        return left;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {1, 3, 5, 6},
        {1, 3, 5, 6},
        {1, 3, 5, 6},
    };
    vector<int> targets = {5, 2, 7};
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.searchInsert(nums[group], targets[group]) << endl;
}
