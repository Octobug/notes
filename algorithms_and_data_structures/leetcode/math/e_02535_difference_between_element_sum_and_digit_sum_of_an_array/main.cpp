#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int differenceOfSum(vector<int> &nums)
    {
        int elemSum = 0, digitSum = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            elemSum += nums[i];

            int num = nums[i];
            while (num > 0)
            {
                digitSum += num % 10;
                num /= 10;
            }
        }

        return abs(elemSum - digitSum);
    }
};

int main()
{
    vector<vector<int>> nums = {
        {1, 15, 6, 3}, // 9
        {1, 2, 3, 4},  // 0
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.differenceOfSum(nums[group]) << endl;

    return 0;
}
