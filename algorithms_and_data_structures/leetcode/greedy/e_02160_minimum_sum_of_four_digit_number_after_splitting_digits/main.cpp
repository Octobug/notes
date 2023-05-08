#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int minimumSum(int num)
    {
        vector<int> nums;
        for (int i = 0; i < 4; ++i)
        {
            nums.push_back(num % 10);
            num /= 10;
        }

        sort(nums.begin(), nums.end());

        int new1 = nums[0] * 10 + nums[2];
        int new2 = nums[1] * 10 + nums[3];

        return new1 + new2;
    }
};

int main()
{
    int num1 = 2932;
    int num2 = 4009;

    vector<int> groups = {num1, num2};
    int group;

    cout << "Please input group: ";
    cin >> group;

    Solution s;
    cout << s.minimumSum(groups[group - 1]) << endl;

    return 0;
}
