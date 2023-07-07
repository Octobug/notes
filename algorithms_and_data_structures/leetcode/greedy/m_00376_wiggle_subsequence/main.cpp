#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int wiggleMaxLength(vector<int> &nums)
    {
        int count = 1;
        if (nums.size() == 1)
            return count;

        bool sign;
        for (int i = 1; i < nums.size(); i++)
        {
            int diff = nums[i] - nums[i - 1];
            if (diff != 0)
            {
                if (count == 1)
                    sign = (diff > 0);
                if (diff > 0 == sign)
                {
                    count++;
                    sign = !sign;
                }
            }
        }

        return count;
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {1, 7, 4, 9, 2, 5},
        {1, 17, 5, 10, 13, 15, 10, 5, 16, 8},
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {0, 0},
        {3, 3, 3, 2, 5},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.wiggleMaxLength(inputs[group]) << endl;

    return 0;
}
