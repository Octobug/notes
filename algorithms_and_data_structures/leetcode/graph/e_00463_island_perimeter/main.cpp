#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int area = 0;
    int border = 0;
    int row, col;
    vector<vector<bool>> visited;
    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    void dfs(vector<vector<int>> &grid, int x, int y)
    {
        area++;
        visited[x][y] = true;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dir[i][0];
            int ny = y + dir[i][1];

            if (nx < 0 || nx >= row || ny < 0 || ny >= col)
                continue;

            if (grid[nx][ny] == 1)
                border++;
            else
                continue;

            if (visited[nx][ny])
                continue;

            dfs(grid, nx, ny);
        }
    }

    int islandPerimeter(vector<vector<int>> &grid)
    {
        row = grid.size();
        col = grid[0].size();
        visited = vector<vector<bool>>(row, vector<bool>(col, false));

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (grid[i][j] == 1)
                {
                    dfs(grid, i, j);
                    return area * 4 - border;
                }
            }
        }

        return 0;
    }
};

int main()
{
    vector<vector<vector<int>>> grids = {
        {
            {0, 1, 0, 0},
            {1, 1, 1, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0},
        }, // 16
        {
            {1},
        }, // 4
        {
            {1, 0},
        }, // 4
        {
            {1, 1},
            {1, 1},
        }, // 8
        {
            {1, 1},
        }, // 6
        {
            {1, 1, 0},
            {1, 1, 0},
        }, // 8
        {
            {1, 0},
            {1, 0},
        }, // 6
        {
            {1, 1},
            {1, 0},
        }, // 8
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.islandPerimeter(grids[group]) << endl;

    return 0;
}
