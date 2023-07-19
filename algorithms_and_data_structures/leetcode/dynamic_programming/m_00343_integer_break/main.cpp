#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int integerBreak(int n)
    {
        int dp[n + 1];

        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 1;

        for (int i = 3; i <= n; i++)
        {
            dp[i] = 0;
            for (int j = 1; j <= i / 2; j++)
                dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]));
        }

        return dp[n];
    }
};

int main()
{
    int n;
    cout << "Please input n: ";
    cin >> n;

    Solution s;
    cout << s.integerBreak(n) << endl;

    return 0;
}
