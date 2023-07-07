#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int maxSum = INT_MIN;
        int sum = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            maxSum = max(sum, maxSum);
            if (sum < 0)
                sum = 0;
        }

        return maxSum;
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {-2, 1, -3, 4, -1, 2, 1, -5, 4},
        {1},
        {5, 4, -1, 7, 8},
        {-2, -1},
        {8, -19, 5, -4, 20},
        {1, -1, -2},
        {0, -3, 1, 1},
        {-3, 2, -1},
        {-1, -2, -2, -2, 3, 2, -2, 0},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maxSubArray(inputs[group]) << endl;

    return 0;
}
