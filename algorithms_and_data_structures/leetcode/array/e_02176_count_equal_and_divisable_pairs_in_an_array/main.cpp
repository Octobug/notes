#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int countPairs(vector<int> &nums, int k)
    {
        int result = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            int isIEven = i % k == 0;
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (nums[i] != nums[j])
                    continue;

                if (i * j % k != 0)
                    continue;

                result++;
            }
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {3, 1, 2, 2, 2, 1, 3},                                     // 4
        {1, 2, 3, 4},                                              // 0
        {5, 5, 9, 2, 5, 5, 9, 2, 2, 5, 5, 6, 2, 2, 5, 2, 5, 4, 3}, // 18
    };
    vector<int> ks = {2, 1, 7};
    int group = getGroup();
    Solution s;
    cout << s.countPairs(nums[group], ks[group]) << endl;

    return 0;
}
