#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int left = 0;
        int min_len = nums.size() + 1;
        int sum = 0;

        for (int right = 0; right < nums.size(); right++)
        {
            sum += nums[right];
            while (sum >= target)
            {
                int cur_leng = right - left + 1;
                if (cur_leng < min_len)
                {
                    min_len = cur_leng;
                }
                sum -= nums[left];
                left++;
            }
        }
        return min_len > nums.size() ? 0 : min_len;
    }
};

int main()
{
    vector<int> nums1 = {2, 3, 1, 2, 4, 3};
    vector<int> nums2 = {1, 4, 4};
    vector<int> nums3 = {1, 1, 1, 1, 1, 1, 1, 1};
    vector<int> nums4 = {2, 4, 9, 2, 4, 5, 13};

    vector<vector<int>> groups = {nums1, nums2, nums3, nums4};

    int group;
    cout << "Please input group: ";
    cin >> group;

    int target;
    cout << "Please input target: ";
    cin >> target;

    Solution s;
    cout << s.minSubArrayLen(target, groups[group - 1]) << endl;

    return 0;
}
