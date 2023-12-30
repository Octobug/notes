#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    bool isSameAfterReversals(int num)
    {
        if (num == 0 || num % 10 != 0)
            return true;

        return false;
    }
};

int main()
{
    vector<int> nums = {
        526,  // 1
        1800, // 0
        0,    // 1
    };

    int group = getGroup();

    Solution s;
    cout << s.isSameAfterReversals(nums[group]) << endl;

    return 0;
}
