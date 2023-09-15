#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int theMaximumAchievableX(int num, int t)
    {
        return num + t * 2;
    }
};

int main()
{
    vector<int> nums = {
        4, // 4
        3, // 7
    };
    vector<int> ts = {
        1,
        2,
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.theMaximumAchievableX(nums[group], ts[group]) << endl;

    return 0;
}
