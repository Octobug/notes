#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int findNumberOfLIS(vector<int> &nums)
    {
        int len = nums.size();
        int dpLength[len];
        int dpCount[len];
        int maxCount = 1;

        for (int i = 0; i < nums.size(); i++)
        {
            dpLength[i] = 1;
            dpCount[i] = 1;
            for (int j = 0; j < i; j++)
            {
                if (nums[i] > nums[j])
                {
                    if (dpLength[j] + 1 > dpLength[i])
                    {
                        dpLength[i] = dpLength[j] + 1;
                        dpCount[i] = dpCount[j];
                    }
                    else if (dpLength[j] + 1 == dpLength[i])
                    {
                        dpCount[i] += dpCount[j];
                    }
                }

                maxCount = max(maxCount, dpLength[i]);
            }
        }

        int result = 0;
        for (int i = 0; i < len; i++)
        {
            if (maxCount == dpLength[i])
                result += dpCount[i];
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {1, 3, 5, 4, 7}, // 2
        {2, 2, 2, 2, 2}, // 5
        {1},             // 1
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.findNumberOfLIS(nums[group]) << endl;

    return 0;
}
