#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int sumOfSquares(vector<int> &nums)
    {
        int n = nums.size();
        int result = 0;

        for (int i = 0; i < n; i++)
        {
            if (n % (i + 1) == 0)
                result += nums[i] * nums[i];
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {1, 2, 3, 4},         // 21
        {2, 7, 1, 19, 18, 3}, // 63
    };

    int group = getGroup();
    Solution s;
    cout << s.sumOfSquares(nums[group]) << endl;

    return 0;
}
