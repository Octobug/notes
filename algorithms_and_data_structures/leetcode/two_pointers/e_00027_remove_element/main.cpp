#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    int removeElement(vector<int> &nums, int val)
    {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right)
        {
            while (left <= right && val != nums[left])
            {
                left++;
            }
            while (right >= left && val == nums[right])
            {
                right--;
            }

            if (left < right)
            {
                nums[left] = nums[right];
                nums[right] = val;
            }
        }
        return left;
    }
};

int main()
{
    Solution s;

    vector<int> nums1 = {3, 2, 2, 3};
    vector<int> nums2 = {0, 1, 2, 2, 3, 0, 4, 2};
    vector<int> nums3 = {2};

    vector<vector<int>> groups = {nums1, nums2, nums3};

    int val;
    int group;

    cout << "Please input group: ";
    cin >> group;

    cout << "Please input val: ";
    cin >> val;

    int k = s.removeElement(groups[group - 1], val);
    cout << "k: " << k << endl;
}
