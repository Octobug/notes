#include <iostream>
#include <queue>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<vector<bool>> visited;
    int direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    queue<pair<int, int>> que;

    int bfs(vector<vector<int>> &grid, int x, int y)
    {
        int result = 1;
        int row = grid.size();
        int col = grid[0].size();

        que.push({x, y});
        visited[x][y] = true;
        while (!que.empty())
        {
            pair<int, int> cur = que.front();
            que.pop();
            for (int i = 0; i < 4; i++)
            {
                int ni = cur.first + direction[i][0];
                int nj = cur.second + direction[i][1];
                if (ni >= 0 && ni < row &&
                    nj >= 0 && nj < col)
                {
                    if (grid[ni][nj] != 1 || visited[ni][nj])
                        continue;

                    visited[ni][nj] = true;
                    que.push({ni, nj});
                    result++;
                }
            }
        }

        return result;
    }

    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        int row = grid.size();
        int col = grid[0].size();
        int result = 0;
        visited = vector<vector<bool>>(row, vector<bool>(col, false));

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (grid[i][j] != 1 || visited[i][j])
                    continue;

                result = max(result, bfs(grid, i, j));
            }
        }

        return result;
    }
};

int main()
{
    vector<vector<vector<int>>> grids = {
        {
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
            {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
            {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
        }, // 6
        {
            {0, 0, 0, 0, 0, 0, 0, 0},
        }, // 0
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maxAreaOfIsland(grids[group]) << endl;

    return 0;
}
