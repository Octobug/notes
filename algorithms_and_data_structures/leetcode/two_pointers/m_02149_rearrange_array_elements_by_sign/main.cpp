#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> rearrangeArray(vector<int> &nums)
    {
        vector<int> result(nums.size());

        int pi = 0, ni = 1;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > 0)
            {
                result[pi] = nums[i];
                pi += 2;
            }
            else
            {
                result[ni] = nums[i];
                ni += 2;
            }
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {3, 1, -2, -5, 2, -4}, // [3,-2,1,-5,2,-4]
        {-1, 1},               // [1,-1]
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<int> result = s.rearrangeArray(nums[group]);
    output(result);

    return 0;
}
