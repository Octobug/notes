#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool canJump(vector<int> &nums)
    {
        int stepLeft = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            stepLeft--;

            if (stepLeft < 0)
                return false;

            stepLeft = max(stepLeft, nums[i]);

            if (stepLeft >= nums.size() - i - 1)
                return true;
        }

        return stepLeft >= 0;
    }
};

class SolutionOther
{
public:
    bool canJump(vector<int> &nums)
    {
        int cover = 0;
        if (nums.size() == 1)
            return true;
        for (int i = 0; i <= cover; i++)
        {
            cover = max(i + nums[i], cover);
            if (cover >= nums.size() - 1)
                return true;
        }
        return false;
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {2, 3, 1, 1, 4},
        {3, 2, 1, 0, 4},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.canJump(inputs[group]) << endl;
}
