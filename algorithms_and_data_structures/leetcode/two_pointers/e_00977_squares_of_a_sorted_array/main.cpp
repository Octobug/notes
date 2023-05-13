#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> sortedSquares(vector<int> &nums)
    {
        int left = 0, right = nums.size() - 1;

        if (nums[left] >= 0)
        {
            for (int i = 0; i < nums.size(); i++)
            {
                nums[i] *= nums[i];
            }
        }
        else if (nums[right] <= 0)
        {
            for (int i = 0; i < nums.size() / 2; i++)
            {
                int left = nums[i];
                int r_index = nums.size() - 1 - i;
                int right = nums[r_index];
                int tmp = left;

                nums[i] = right * right;
                nums[r_index] = tmp * tmp;
            }
            if (nums.size() % 2 != 0)
            {
                int mid = nums.size() / 2;
                nums[mid] *= nums[mid];
            }
        }
        else
        {
            vector<int> result(nums.size(), 0);
            int l_idx = 0;
            int r_idx = nums.size() - 1;

            for (int i = result.size() - 1; i >= 0; i--)
            {
                int l_square = nums[l_idx] * nums[l_idx];
                int r_square = nums[r_idx] * nums[r_idx];

                if (l_square > r_square)
                {
                    result[i] = l_square;
                    l_idx++;
                }
                else
                {
                    result[i] = r_square;
                    r_idx--;
                }
            }
            return result;
        }
        return nums;
    }
};

int main()
{
    vector<int> nums1 = {-4, -1, 0, 3, 10};
    vector<int> nums2 = {-7, -3, 2, 3, 11};
    vector<int> nums3 = {-5, -3, -2, -1};
    vector<int> nums4 = {-4, 0, 1, 1};
    vector<int> nums5 = {-5, -4, 1, 2, 5};
    vector<int> nums6 = {-1};
    vector<int> nums7 = {0, 2};
    vector<int> nums8 = {-4, -3, -2, 3, 3};
    vector<int> nums9 = {-9, -7, -5, -3, -1, 2, 4, 4, 7, 10};

    vector<vector<int>> groups = {nums1, nums2, nums3, nums4, nums5, nums6, nums7, nums8, nums9};

    cout << "Please input group: ";

    int group;

    cin >> group;

    Solution s;
    vector<int> result = s.sortedSquares(groups[group - 1]);

    output(result);

    return 0;
}
