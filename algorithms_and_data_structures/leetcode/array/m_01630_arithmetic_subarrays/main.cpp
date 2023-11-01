#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<bool> checkArithmeticSubarrays(vector<int> &nums, vector<int> &l, vector<int> &r)
    {
        vector<bool> result;

        for (int i = 0; i < l.size(); i++)
        {
            vector<int> subarray = {nums.begin() + l[i],
                                    nums.begin() + r[i] + 1};

            sort(subarray.begin(), subarray.end());
            int diff = subarray[1] - subarray[0];
            int j = 1;
            for (; j < subarray.size(); j++)
            {
                if (subarray[j] - subarray[j - 1] != diff)
                {
                    result.push_back(false);
                    break;
                }
            }
            if (j == subarray.size())
                result.push_back(true);
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {4, 6, 5, 9, 3, 7},                                 // [true,false,true]
        {-12, -9, -3, -12, -6, 15, 20, -25, -20, -15, -10}, // [false,true,false,false,true,true]
    };
    vector<vector<int>> ls = {
        {0, 0, 2},
        {0, 1, 6, 4, 8, 7},
    };
    vector<vector<int>> rs = {
        {2, 3, 5},
        {4, 4, 9, 7, 9, 10},
    };

    int group;
    cout << "Please enter group: ";
    cin >> group;
    group--;

    Solution s;
    vector<bool> result = s.checkArithmeticSubarrays(
        nums[group], ls[group], rs[group]);

    output<bool>(result);

    return 0;
}
