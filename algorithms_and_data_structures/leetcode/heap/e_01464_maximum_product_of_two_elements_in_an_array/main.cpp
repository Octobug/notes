#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxProduct(vector<int> &nums)
    {
        int less = min(nums[0], nums[1]);
        int more = max(nums[0], nums[1]);

        for (int i = 2; i < nums.size(); i++)
        {
            if (nums[i] > less)
            {
                less = min(nums[i], more);
                more = max(nums[i], more);
            }
        }

        return (less - 1) * (more - 1);
    }
};

int main()
{
    vector<vector<int>> nums = {
        {3, 4, 5, 2}, // 12
        {1, 5, 4, 5}, // 16
        {3, 7},       // 12
    };

    int group;
    cout << "Please enter group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maxProduct(nums[group]) << endl;

    return 0;
}
