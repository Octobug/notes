#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int lastStoneWeightII(vector<int> &stones)
    {
        int sum = 0;
        for (int i = 0; i < stones.size(); i++)
            sum += stones[i];

        int half = sum / 2;

        vector<int> dp(half + 1, 0);
        for (int i = 0; i < stones.size(); i++)
        {
            for (int j = half; j >= stones[i]; j--)
            {
                dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
            }
        }

        return sum - dp[half] - dp[half];
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {2, 7, 4, 1, 8, 1},
        {31, 26, 33, 21, 40},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.lastStoneWeightII(inputs[group]) << endl;

    return 0;
}
