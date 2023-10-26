#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maximizeSum(vector<int> &nums, int k)
    {
        int maxnum = nums[0];

        for (int i = 1; i < nums.size(); i++)
            maxnum = max(maxnum, nums[i]);

        return maxnum * k + k * (k - 1) / 2;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {1, 2, 3, 4, 5}, // 18
        {5, 5, 5},       // 11
    };
    vector<int> ks = {3, 2};

    int group;
    cout << "Please enter group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maximizeSum(nums[group], ks[group]) << endl;

    return 0;
}
