#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    vector<int> runningSum(vector<int> &nums)
    {
        for (int i = 1; i < nums.size(); ++i)
        {
            nums[i] += nums[i - 1];
        }
        return nums;
    }
};

int main()
{
    Solution s;
    vector<int> in = {1, 2, 3, 4};
    vector<int> res = s.runningSum(in);

    cout << '[';
    for (int i = 0; i < res.size(); ++i)
    {
        cout << res[i];
        if (i != res.size() - 1)
        {
            cout << ',';
        }
    }
    cout << ']' << endl;
}
