#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int numTrees(int n)
    {
        int dp[n + 1];

        dp[0] = 1;

        for (int i = 1; i <= n; i++)
        {
            dp[i] = 0;
            for (int j = 0; j < i; j++)
                dp[i] += dp[j] * dp[i - j - 1];
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
    cout << s.numTrees(n) << endl;

    return 0;
}
