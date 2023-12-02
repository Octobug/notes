#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

// https://leetcode.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/solutions/4139929/simple-solution-beginner-friendly-easy-to-understand/
class Solution
{
public:
  int dp[51][101][51], pre[51][101][51], mod = 1e9 + 7;
  // dp[len][cost][max_val]

  int numOfArrays(int n, int m, int k)
  {
    for (int i = 0; i <= m; i++)
    {
      dp[1][i][1] = 1;
      pre[1][i][1] = i;
    }

    for (int len = 2; len <= n; len++)
    {
      for (int mx = 1; mx <= m; mx++)
      {
        for (int cost = 1; cost <= k; cost++)
        {
          // In this first case, we can append any element from
          //  [1, mx] to the end of the array.
          dp[len][mx][cost] = (1LL * mx * dp[len - 1][mx][cost]) % mod;

          // In this second case, we can append the element "mx" to the end of
          //  the array.
          dp[len][mx][cost] = (dp[len][mx][cost] +
                               pre[len - 1][mx - 1][cost - 1]) %
                              mod;

          pre[len][mx][cost] = (pre[len][mx - 1][cost] + dp[len][mx][cost]) %
                               mod;
        }
      }
    }
    return pre[n][m][k];
  }
};

int main()
{
  vector<vector<int>> inputs = {
      {2, 3, 1},     // 6
      {5, 2, 3},     // 0
      {9, 1, 1},     // 1
      {50, 100, 25}, // 34549172
  };

  int group = getGroup();
  vector<int> nmk = inputs[group];

  Solution s;
  cout << s.numOfArrays(nmk[0], nmk[1], nmk[2]) << endl;

  return 0;
}
