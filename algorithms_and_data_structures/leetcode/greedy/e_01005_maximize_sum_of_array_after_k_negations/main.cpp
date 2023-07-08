#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
    static bool cmp(int a, int b)
    {
        return abs(a) < abs(b);
    }

public:
    int largestSumAfterKNegations(vector<int> &nums, int k)
    {
        sort(nums.begin(), nums.end(), cmp);

        for (int i = nums.size() - 1; i >= 0 && k > 0; i--)
            if (nums[i] < 0)
            {
                nums[i] = -nums[i];
                k--;
            }

        if (k % 2 == 1)
            nums[0] = -nums[0];

        int sum = 0;
        for (int num : nums)
            sum += num;

        return sum;
    }
};

int main()
{
    vector<vector<vector<int>>> inputs = {
        {{4, 2, 3}, {1}},
        {{3, -1, 0, 2}, {3}},
        {{2, -3, -1, 5, -4}, {2}},
        {{-8, 3, -5, -3, -5, -2}, {6}},
        {{-2, 5, 0, 2, -2}, {3}},
        {{8, -7, -3, -9, 1, 9, -6, -9, 3}, {8}},
        {{-4, -2, -3}, {4}},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.largestSumAfterKNegations(inputs[group][0], inputs[group][1][0]) << endl;

    return 0;
}
