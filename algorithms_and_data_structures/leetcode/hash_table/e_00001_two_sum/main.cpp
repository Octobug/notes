#include <iostream>
#include <unordered_map>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++)
        {
            int complement = target - nums[i];
            if (map.count(nums[i]))
            {
                return {map[nums[i]], i};
            }
            map[complement] = i;
        }
        return {};
    }
};

int main()
{
    vector<int> nums1 = {2, 7, 11, 15};
    vector<int> nums2 = {3, 2, 4};
    vector<int> nums3 = {3, 3};

    vector<vector<int>> groups = {nums1, nums2, nums3};

    int group;
    cout << "Please input group: ";
    cin >> group;

    int target;
    cout << "Please input target: ";
    cin >> target;

    Solution s;
    vector<int> result = s.twoSum(groups[group - 1], target);

    output(result);

    return 0;
}
