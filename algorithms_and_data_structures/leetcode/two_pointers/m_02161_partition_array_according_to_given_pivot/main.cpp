#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> pivotArray(vector<int> &nums, int pivot)
    {
        int left = 0, right = nums.size() - 1;
        vector<int> result(nums.size(), pivot);

        for (int i = left; i <= right; i++)
        {
            if (nums[i] < pivot)
                result[left++] = nums[i];
        }

        for (int i = right; i >= 0; i--)
        {
            if (nums[i] > pivot)
                result[right--] = nums[i];
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {9, 12, 5, 10, 14, 3, 10}, // [9,5,3,10,10,12,14]
        {-3, 4, 3, 2},             // [-3,2,4,3]
    };
    vector<int> pivots = {10, 2};

    int group;
    cout << "Please input group: " << endl;
    cin >> group;
    group--;

    Solution s;
    vector<int> result = s.pivotArray(nums[group], pivots[group]);
    output(result);

    return 0;
}
