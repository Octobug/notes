#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int jump(vector<int> &nums)
    {
        int count = 0;
        int nextReachedIndex = 0;
        int reachedIndex = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            if (reachedIndex >= nums.size() - 1)
                break;

            nextReachedIndex = max(nextReachedIndex, i + nums[i]);

            if (i == reachedIndex)
            {
                count++;
                reachedIndex = nextReachedIndex;
            }
        }

        return count;
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {2, 3, 1, 1, 4},
        {2, 3, 0, 1, 4},
        {0},
        {1, 2},
        {2, 3, 1},
        {7, 0, 9, 6, 9, 6, 1, 7, 9, 0, 1, 2, 9, 0, 3},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.jump(inputs[group]) << endl;

    return 0;
}
