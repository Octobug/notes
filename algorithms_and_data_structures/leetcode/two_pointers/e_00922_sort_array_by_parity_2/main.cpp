#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> sortArrayByParityII(vector<int> &nums)
    {
        int evenIndex = 0, oddIndex = 1;
        while (evenIndex < nums.size() && oddIndex < nums.size())
        {
            if (nums[evenIndex] % 2 == 0)
                evenIndex += 2;
            else if (nums[oddIndex] % 2 != 0)
                oddIndex += 2;
            else
            {
                swap(nums[evenIndex], nums[oddIndex]);
                evenIndex += 2;
                oddIndex += 2;
            }
        }
        return nums;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {4, 2, 5, 7},
        {2, 3},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<int> result = s.sortArrayByParityII(nums[group]);
    output(result);

    return 0;
}
