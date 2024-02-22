#include <iostream>
#include <unordered_set>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int countDistinctIntegers(vector<int> &nums)
    {
        int result = 0;
        unordered_set<int> uset;

        for (int i = 0; i < nums.size(); i++)
        {
            int num = nums[i];
            int reversed = 0;

            uset.insert(num);
            while (num > 0)
            {
                reversed = reversed * 10 + num % 10;
                num /= 10;
            }

            uset.insert(reversed);
        }

        return uset.size();
    }
};

int main()
{
    vector<vector<int>> nums = {
        {1, 13, 10, 12, 31}, // 6
        {2, 2, 2},           // 1
    };

    int group = getGroup();

    Solution s;
    cout << s.countDistinctIntegers(nums[group]) << endl;

    return 0;
}
