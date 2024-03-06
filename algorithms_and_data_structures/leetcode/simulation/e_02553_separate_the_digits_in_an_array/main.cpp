#include <iostream>
#include <vector>
#include "array.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    vector<int> separateDigits(vector<int> &nums)
    {
        vector<int> result;
        for (auto &num : nums)
        {
            string str = to_string(num);
            for (auto &c : str)
                result.push_back(c - '0');
        }
        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {13, 25, 83, 77}, // 1,3,2,5,8,3,7,7
        {7, 1, 3, 9},     // 7,1,3,9
    };

    int group = getGroup();

    Solution s;
    vector<int> result = s.separateDigits(nums[group]);
    output(result);

    return 0;
}
