#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    void rotate(vector<int> &nums, int k)
    {
        k = k % nums.size();
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};

int main()
{
    vector<vector<int>> nums = {
        {1, 2, 3, 4, 5, 6, 7}, // 5,6,7,1,2,3,4
        {-1, -100, 3, 99},     // 3,99,-1,-100
    };
    vector<int> ks = {3, 2};
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    s.rotate(nums[group], ks[group]);
    output(nums[group]);

    return 0;
}
