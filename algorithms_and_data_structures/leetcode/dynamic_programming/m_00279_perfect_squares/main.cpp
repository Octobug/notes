#include <cmath>
#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int numSquares(int n)
    {
        int pslen = sqrt(n);
        int psquares[pslen];

        for (int i = 1; i <= pslen; i++)
            psquares[i - 1] = i * i;

        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;

        for (int i = 0; i < pslen; i++)
            for (int j = psquares[i]; j <= n; j++)
                // psquares[1] 中的元素是 1，随着 j++，dp[1]-dp[end] 第一遍都被赋值了
                // 所以不需要 if (dp[j - psquares[i]] != INT_MAX) 这个判断
                dp[j] = min(dp[j], dp[j - psquares[i]] + 1);

        return dp[n];
    }
};

int main()
{
    // 12, 3
    // 13, 2
    int n;
    cout << "Please input n: ";
    cin >> n;
    Solution s;
    cout << s.numSquares(n) << endl;

    return 0;
}
