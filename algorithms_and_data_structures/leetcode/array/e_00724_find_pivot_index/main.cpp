#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class SolutionPrefixSum
{
public:
    int pivotIndex(vector<int> &nums)
    {
        int len = nums.size();
        int presum[len];

        for (int i = 0; i < len; i++)
            presum[i] = 0;

        for (int i = len - 2; i >= 0; i--)
            presum[i] = presum[i + 1] + nums[i + 1];

        if (presum[0] == 0)
            return 0;

        presum[0] = 0;
        for (int i = 1; i < len; i++)
            if (presum[i] == presum[i - 1] + nums[i - 1])
                return i;
            else
                presum[i] = presum[i - 1] + nums[i - 1];

        return -1;
    }
};

class Solution
{
public:
    int pivotIndex(vector<int> &nums)
    {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
            sum += nums[i];

        int leftSum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (leftSum == sum - nums[i])
                return i;
            leftSum += nums[i];
            sum -= nums[i];
        }
        return -1;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {1, 7, 3, 6, 5, 6},     // 3
        {1, 2, 3},              // -1
        {2, 1, -1},             // 0
        {-1, -1, 0, 0, -1, -1}, // 2
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.pivotIndex(nums[group]) << endl;

    return 0;
}
