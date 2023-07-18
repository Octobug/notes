#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        int dp[m][n];

        if (obstacleGrid[0][0] == 1)
            return 0;

        dp[0][0] = 1;

        for (int i = 1; i < n; i++)
        {
            if (dp[0][i - 1] != 1 || obstacleGrid[0][i] == 1)
                dp[0][i] = 0;
            else
                dp[0][i] = 1;
        }

        for (int i = 1; i < m; i++)
        {
            if (dp[i - 1][0] != 1 || obstacleGrid[i][0] == 1)
                dp[i][0] = 0;
            else
                dp[i][0] = 1;
        }

        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (obstacleGrid[i][j] == 1)
                    dp[i][j] = 0;
                else
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }

        return dp[m - 1][n - 1];
    }
};

int main()
{
    vector<vector<vector<int>>> inputs = {
        {
            {0, 0, 0},
            {0, 1, 0},
            {0, 0, 0},
        },
        {
            {0, 1},
            {0, 0},
        },
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.uniquePathsWithObstacles(inputs[group]) << endl;

    return 0;
}
