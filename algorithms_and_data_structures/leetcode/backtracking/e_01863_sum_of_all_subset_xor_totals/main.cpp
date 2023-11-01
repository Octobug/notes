#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int result = 0;
    int subset[12];
    int count = 0;

    void backtrack(vector<int> &nums, int begin)
    {
        for (int i = begin; i < nums.size(); i++)
        {
            subset[count++] = nums[i];

            int xorSum = subset[0];
            for (int i = 1; i < count; i++)
                xorSum ^= subset[i];
            result += xorSum;

            backtrack(nums, i + 1);
            count--;
        }
    }

    int subsetXORSum(vector<int> &nums)
    {
        backtrack(nums, 0);
        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {1, 3},             // 6
        {5, 1, 6},          // 28
        {3, 4, 5, 6, 7, 8}, // 480
    };

    int group;
    cout << "Please enter group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.subsetXORSum(nums[group]) << endl;

    return 0;
}
