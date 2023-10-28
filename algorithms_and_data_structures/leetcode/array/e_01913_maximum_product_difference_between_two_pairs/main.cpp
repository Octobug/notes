#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxProductDifference(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int len = nums.size();

        return nums[len - 1] * nums[len - 2] - nums[0] * nums[1];
    }
};

int main()
{
    vector<vector<int>> nums = {
        {5, 6, 2, 7, 4},       // 34
        {4, 2, 5, 9, 7, 4, 8}, // 64
    };

    int group;
    cout << "Please enter group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maxProductDifference(nums[group]) << endl;

    return 0;
}
