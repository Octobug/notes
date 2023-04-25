#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    vector<int> buildArray(vector<int> &nums)
    {
        int mul = 1000;
        for (int i = 0; i < nums.size(); i++)
        {
            nums[i] = nums[i] + (mul * (nums[nums[i]] % mul));
        }
        for (int i = 0; i < nums.size(); i++)
        {
            nums[i] /= mul;
        }
        return nums;
    }
};

int main()
{
    Solution s;
    vector<int> in1 = {0, 2, 1, 5, 3, 4};
    vector<int> in2 = {5, 0, 1, 2, 3, 4};
    vector<int> res1 = s.buildArray(in1);
    vector<int> res2 = s.buildArray(in2);
    output(res1);
    output(res2);
}
