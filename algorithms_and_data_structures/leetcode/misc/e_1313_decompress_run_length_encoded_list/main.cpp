#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    vector<int> decompressRLElist(vector<int> &nums)
    {
        int size = 0;
        for (int i = 0; i < nums.size(); i += 2)
        {
            size += nums[i];
        }

        vector<int> ans(size);
        int count = 0;
        for (int i = 0; i < nums.size(); i += 2)
        {
            fill(ans.begin() + count,
                 ans.begin() + count + nums[i],
                 nums[i + 1]);
            count += nums[i];
        }

        return ans;
    }
};

int main()
{
    Solution s;

    vector<int> nums = {1, 2, 3, 4};
    vector<int> ans = s.decompressRLElist(nums);
    output(ans);

    nums = {1, 1, 2, 3};
    ans = s.decompressRLElist(nums);
    output(ans);
}
