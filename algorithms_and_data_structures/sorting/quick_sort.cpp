#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    void qsort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
        {
            return;
        }

        int i = left;
        int j = right;
        int pivot = nums[left];

        while (i < j)
        {
            while (i < j && nums[j] >= pivot)
            {
                --j;
            }
            nums[i] = nums[j];

            while (i < j && nums[i] <= pivot)
            {
                ++i;
            }
            nums[j] = nums[i];
        }

        nums[i] = pivot;

        qsort(nums, left, i - 1);
        qsort(nums, i + 1, right);
    }
};

int main()
{
    vector<vector<int>> arrays = {{
        {11, 25, 66, 1, 69, 7},
        {23, 55, 17, 45, 15, 52},
        {75, 31, 36, 44, 58, 8},
        {22, 27, 33, 25, 68, 4},
        {84, 28, 14, 11, 5, 50},
    }};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    s.qsort(arrays[group], 0, arrays[group].size() - 1);
    output(arrays[group]);

    return 0;
}
