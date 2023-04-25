#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        int slow = 0;

        for (int fast = 1; fast < nums.size(); fast++)
        {
            if (nums[slow] != nums[fast])
            {
                nums[++slow] = nums[fast];
            }
        }

        return slow + 1;
    }
};

int main()
{
    Solution s;

    vector<int> nums1 = {1, 1, 2};
    vector<int> nums2 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};

    vector<vector<int>> groups = {nums1, nums2};

    int group;

    cout << "Please input group: ";
    cin >> group;

    int k = s.removeDuplicates(groups[group - 1]);
    cout << "k: " << k << endl;
}
