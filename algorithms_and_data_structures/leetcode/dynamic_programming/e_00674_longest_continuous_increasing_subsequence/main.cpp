#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int findLengthOfLCIS(vector<int> &nums)
    {
        int result = 1;
        int count = 1;

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] > nums[i - 1])
            {
                count++;
                result = max(result, count);
            }
            else
            {
                count = 1;
            }
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {1, 3, 5, 4, 7}, // 3
        {2, 2, 2, 2, 2}, // 1
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.findLengthOfLCIS(nums[group]) << endl;

    return 0;
}
