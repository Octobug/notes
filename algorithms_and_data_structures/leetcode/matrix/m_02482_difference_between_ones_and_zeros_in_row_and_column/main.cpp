#include <iostream>
#include <vector>
#include "array.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    vector<vector<int>> onesMinusZeros(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> result(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++)
        {
            int ones = 0;
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 1)
                    ones++;

            int zeros = n - ones;

            for (int j = 0; j < n; j++)
                result[i][j] = ones - zeros;
        }

        for (int j = 0; j < n; j++)
        {
            int ones = 0;
            for (int i = 0; i < m; i++)
                if (grid[i][j] == 1)
                    ones++;

            int zeros = m - ones;

            for (int i = 0; i < m; i++)
                result[i][j] += ones - zeros;
        }

        return result;
    }
};

int main()
{
    vector<vector<vector<int>>> grids = {
        {
            {0, 1, 1},
            {1, 0, 1},
            {0, 0, 1},
        }, // [[0,0,4],[0,0,4],[-2,-2,2]]
        {
            {1, 1, 1},
            {1, 1, 1},
        }, // [[5,5,5],[5,5,5]]
    };

    int group = getGroup();
    Solution s;
    vector<vector<int>> result = s.onesMinusZeros(grids[group]);
    output2d(result);

    return 0;
}
