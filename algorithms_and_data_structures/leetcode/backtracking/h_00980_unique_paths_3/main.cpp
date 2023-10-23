#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int result = 0;
    int startRow = 0, startCol = 0;
    int m, n;
    int emptyCount = 0;
    vector<vector<bool>> visited;
    int dirs[4][2] = {
        {-1, 0},
        {0, -1},
        {1, 0},
        {0, 1},
    };

    void scanMap(vector<vector<int>> &grid)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 0)
                {
                    emptyCount++;
                }
                else if (grid[i][j] == 1)
                {
                    startRow = i;
                    startCol = j;
                }
            }
        }
    }

    void backtrack(vector<vector<int>> &grid, int row, int col)
    {
        for (int i = 0; i < 4; i++)
        {
            int nextRow = row + dirs[i][0];
            int nextCol = col + dirs[i][1];

            if (nextRow < 0 || nextRow >= m || nextCol < 0 || nextCol >= n)
                continue;
            else if (visited[nextRow][nextCol])
                continue;
            else if (grid[nextRow][nextCol] == -1)
                continue;
            else if (grid[nextRow][nextCol] == 2 && emptyCount == 0)
                result++;
            else
            {
                visited[row][col] = true;
                emptyCount--;
                backtrack(grid, nextRow, nextCol);
                visited[nextRow][nextCol] = false;
                emptyCount++;
            }
        }
    }

    int uniquePathsIII(vector<vector<int>> &grid)
    {
        m = grid.size();
        n = grid[0].size();
        visited = vector<vector<bool>>(m, vector<bool>(n, false));

        scanMap(grid);
        backtrack(grid, startRow, startCol);

        return result;
    }
};

int main()
{
    vector<vector<vector<int>>> grids = {
        {
            {1, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 2, -1},
        }, // 2
        {
            {1, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 2},
        }, // 4
        {
            {0, 1},
            {2, 0},
        }, // 0
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.uniquePathsIII(grids[group]) << endl;

    return 0;
}
