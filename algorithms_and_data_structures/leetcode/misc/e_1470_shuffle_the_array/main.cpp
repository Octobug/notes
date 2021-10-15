#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    vector<int> shuffle(vector<int> &nums, int n)
    {
        vector<int> result(n * 2);

        for (int i = 0; i < n; i++)
        {

            result[i * 2] = nums[i];
            result[i * 2 + 1] = nums[i + n];
        }
        return result;
    }
};

int main()
{
    Solution s;
    vector<int> input = {1, 2, 3, 4, 4, 3, 2, 1};
    vector<int> res = s.shuffle(input, input.size() / 2);

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
