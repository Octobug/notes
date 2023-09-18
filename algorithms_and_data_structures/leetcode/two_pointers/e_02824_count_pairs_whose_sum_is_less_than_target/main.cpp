#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int countPairs(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        output(nums);
        int begin = 0, end = nums.size() - 1, count = 0;

        while (begin < end)
        {
            if (nums[begin] + nums[end] < target)
            {
                count += (end - begin);
                begin++;
            }
            else
            {
                end--;
            }
        }

        return count;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {-1, 1, 2, 3, 1},          // 3
        {-6, 2, 5, -2, -7, -1, 3}, // 10
    };
    vector<int> targets = {2, -2};
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.countPairs(nums[group], targets[group]) << endl;

    return 0;
}
