#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    void nextPermutation(vector<int> &nums)
    {
        for (int i = nums.size() - 2; i >= 0; i--)
        {
            for (int j = nums.size() - 1; j > i; j--)
            {
                if (nums[j] > nums[i])
                {
                    swap(nums[j], nums[i]);
                    reverse(nums.begin() + i + 1, nums.end());
                    return;
                }
            }
        }

        reverse(nums.begin(), nums.end());
    }
};

int main()
{
    vector<vector<int>> nums = {
        {1, 2, 3}, // [1,3,2]
        {3, 2, 1}, // [1,2,3]
        {1, 1, 5}, // [1,5,1]
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    s.nextPermutation(nums[group]);
    output(nums[group]);

    return 0;
}
