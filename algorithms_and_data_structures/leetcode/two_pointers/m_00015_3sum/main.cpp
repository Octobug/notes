#include <algorithm>
#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> result;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > 0)
            {
                return result;
            }

            if (i > 0 && nums[i] == nums[i - 1])
            {
                continue;
            }

            int left = i + 1;
            int right = nums.size() - 1;

            while (left < right)
            {
                if (nums[i] + nums[left] + nums[right] > 0)
                {
                    right--;
                }
                else if (nums[i] + nums[left] + nums[right] < 0)
                {
                    left++;
                }
                else
                {
                    result.push_back({nums[i], nums[left], nums[right]});

                    while (left < right && nums[left] == nums[left + 1])
                        left++;

                    while (left < right && nums[right] == nums[right - 1])
                        right--;

                    left--;
                    right--;
                }
            }
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {-1, 0, 1, 2, -1, -4},
        {0, 1, 1},
        {0, 0, 0},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;

    Solution s;
    vector<vector<int>> result = s.threeSum(groups[group - 1]);
    output2d(result);

    return 0;
}
