#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<vector<int>> result;
    vector<vector<int>> visited;
    int row;
    int col;
    int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    void dfs(vector<vector<int>> &heights, int x, int y, int visit)
    {
        if (visited[x][y] == visit || visited[x][y] == 2)
            return;

        if (visited[x][y] == 0)
        {
            visited[x][y] = visit;
        }
        else
        {
            visited[x][y] = 2;
            result.push_back({x, y});
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dir[i][0];
            int ny = y + dir[i][1];

            if (nx < 0 || nx >= row || ny < 0 || ny >= col)
                continue;

            if (heights[x][y] > heights[nx][ny])
                continue;

            dfs(heights, nx, ny, visit);
        }
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        row = heights.size();
        col = heights[0].size();
        visited = vector<vector<int>>(row, vector<int>(col, 0));

        for (int i = 0; i < row; i++)
            dfs(heights, i, 0, 1);
        for (int i = 0; i < col; i++)
            dfs(heights, 0, i, 1);

        for (int i = 0; i < row; i++)
            dfs(heights, i, col - 1, -1);
        for (int i = 0; i < col; i++)
            dfs(heights, row - 1, i, -1);

        return result;
    }
};

int main()
{
    vector<vector<vector<int>>> heights = {
        {
            {1, 2, 2, 3, 5},
            {3, 2, 3, 4, 4},
            {2, 4, 5, 3, 1},
            {6, 7, 1, 4, 5},
            {5, 1, 1, 2, 4},
        }, // [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
        {
            {1},
        }, // [[0,0]]
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<int>> result = s.pacificAtlantic(heights[group]);
    output2d(result);

    return 0;
}
