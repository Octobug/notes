#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int findMiddleIndex(vector<int> &nums)
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
        {2, 3, -1, 8, 4}, // 3
        {1, -1, 4},       // 2
        {2, 5},           // -1
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.findMiddleIndex(nums[group]) << endl;

    return 0;
}
