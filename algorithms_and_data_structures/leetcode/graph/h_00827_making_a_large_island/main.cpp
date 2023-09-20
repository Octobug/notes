#include <iostream>
#include <queue>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<vector<int>> visited;
    int len;
    queue<pair<int, int>> edges;
    int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int islandSize;

    void dfs(vector<vector<int>> &grid, int x, int y, int num)
    {
        if (grid[x][y] != 1 || visited[x][y] == -1)
            return;

        visited[x][y] = -1;
        islandSize++;
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dir[i][0];
            int ny = y + dir[i][1];

            if (nx < 0 || nx >= len || ny < 0 || ny >= len)
                continue;

            if (visited[nx][ny] == -1)
                continue;

            if (grid[nx][ny] != 1 && visited[nx][ny] != num)
            {
                visited[nx][ny] = num;
                edges.push({nx, ny});
                continue;
            }

            dfs(grid, nx, ny, num);
        }
    }

    int largestIsland(vector<vector<int>> &grid)
    {
        len = grid.size();
        visited = vector<vector<int>>(len, vector<int>(len, 0));
        vector<vector<int>> interEdges(len, vector<int>(len, 0));
        int maxIsland = 0;

        int num = 0;
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
            {
                num++;
                islandSize = 0;
                dfs(grid, i, j, num);
                maxIsland = max(maxIsland, islandSize);

                while (!edges.empty())
                {
                    pair<int, int> point = edges.front();
                    edges.pop();

                    interEdges[point.first][point.second] += islandSize;
                }
            }
        }

        int result = 0;
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
                result = max(result, interEdges[i][j]);
        }

        return max(result + 1, maxIsland);
    }
};

int main()
{
    vector<vector<vector<int>>> grids = {
        {
            {1, 0},
            {0, 1},
        }, // 3
        {
            {1, 1},
            {1, 0},
        }, // 4
        {
            {1, 1},
            {1, 1},
        }, // 4
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.largestIsland(grids[group]) << endl;

    return 0;
}
