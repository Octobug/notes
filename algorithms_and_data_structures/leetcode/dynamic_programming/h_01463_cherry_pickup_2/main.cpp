#include <iostream>
#include <vector>
#include "array.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    int cherryPickup(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();

        vector<vector<vector<int>>> dp(m + 1,
                                       vector<vector<int>>(n,
                                                           vector<int>(n, 0)));
        // dp dimensions
        dp[0][0][n - 1] = 0 == n - 1 ? grid[0][0] : grid[0][0] + grid[0][n - 1];
        // row traversing
        for (int row = 1; row < m; row++)
        {
            // avoiding unnecessary column computations
            for (int c1 = 0; c1 < min(n, row + 1); c1++)
            {
                for (int c2 = max(0, n - 1 - row); c2 < n; c2++)
                {
                    int prevMax = 0;
                    // Moves of robos in columns
                    for (int offset1 = max(0, c1 - 1);
                         offset1 <= min(n - 1, c1 + 1);
                         offset1++)
                    {
                        for (int offset2 = max(0, c2 - 1);
                             offset2 <= min(n - 1, c2 + 1);
                             offset2++)
                        {
                            prevMax = max(prevMax,
                                          dp[row - 1][offset1][offset2]);
                        }
                    }
                    // Robo collision condition
                    if (c1 == c2)
                        dp[row][c1][c2] = prevMax + grid[row][c1];
                    else
                        dp[row][c1][c2] = prevMax + grid[row][c1] +
                                          grid[row][c2];
                }
            }
        }
        int res = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                res = max(res, dp[m - 1][i][j]);
            }
        }
        return res;
    }
};

int main()
{
    vector<vector<vector<int>>> grids = {
        {
            {3, 1, 1},
            {2, 5, 1},
            {1, 5, 5},
            {2, 1, 1},
        }, // 24
        {
            {1, 0, 0, 0, 0, 0, 1},
            {2, 0, 0, 0, 0, 3, 0},
            {2, 0, 9, 0, 0, 0, 0},
            {0, 3, 0, 5, 4, 0, 0},
            {1, 0, 2, 3, 0, 0, 6},
        }, // 28
        {
            {1, 0, 0, 3},
            {0, 0, 0, 3},
            {0, 0, 3, 3},
            {9, 0, 3, 3},
        }, // 22
        {
            {8, 8, 10, 9, 1, 7},
            {8, 8, 1, 8, 4, 7},
            {8, 6, 10, 3, 7, 7},
            {3, 0, 9, 3, 2, 7},
            {6, 8, 9, 4, 2, 5},
            {1, 1, 5, 8, 8, 1},
            {5, 6, 5, 2, 9, 9},
            {4, 4, 6, 2, 5, 4},
            {4, 4, 5, 3, 1, 6},
            {9, 2, 2, 1, 9, 3},
        }, // 146
    };

    int group = getGroup();

    Solution s;
    cout << s.cherryPickup(grids[group]) << endl;

    return 0;
}
