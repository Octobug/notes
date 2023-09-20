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

    void bfs(vector<vector<char>> &board, int x, int y)
    {
        int isEnclave = true;
        int row = board.size();
        int col = board[0].size();
        vector<pair<int, int>> todo;

        que.push({x, y});
        visited[x][y] = true;
        while (!que.empty())
        {
            pair<int, int> cur = que.front();
            todo.push_back(cur);
            que.pop();
            for (int i = 0; i < 4; i++)
            {
                int ni = cur.first + direction[i][0];
                int nj = cur.second + direction[i][1];
                if (ni >= 0 && ni < row &&
                    nj >= 0 && nj < col)
                {
                    if (board[ni][nj] != 'O' || visited[ni][nj])
                        continue;

                    visited[ni][nj] = true;
                    que.push({ni, nj});
                }
                else
                {
                    isEnclave = false;
                }
            }
        }

        if (isEnclave)
        {
            for (int i = 0; i < todo.size(); i++)
            {
                pair<int, int> cur = todo[i];
                board[cur.first][cur.second] = 'X';
            }
        }
    }

    void solve(vector<vector<char>> &board)
    {
        int row = board.size();
        int col = board[0].size();
        visited = vector<vector<bool>>(row, vector<bool>(col, false));

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (board[i][j] != 'O' || visited[i][j])
                    continue;

                bfs(board, i, j);
            }
        }
    }
};

class SolutionEdge
{
private:
    int dir[4][2] = {-1, 0, 0, -1, 1, 0, 0, 1};

    void dfs(vector<vector<char>> &board, int x, int y)
    {
        board[x][y] = 'A';
        for (int i = 0; i < 4; i++)
        {
            int nextx = x + dir[i][0];
            int nexty = y + dir[i][1];
            if (nextx < 0 || nextx >= board.size() ||
                nexty < 0 || nexty >= board[0].size())
                continue;

            if (board[nextx][nexty] == 'X' || board[nextx][nexty] == 'A')
                continue;

            dfs(board, nextx, nexty);
        }
        return;
    }

public:
    void solve(vector<vector<char>> &board)
    {
        int n = board.size(), m = board[0].size();
        // 从左侧边，和右侧边向中间遍历
        for (int i = 0; i < n; i++)
        {
            if (board[i][0] == 'O')
                dfs(board, i, 0);
            if (board[i][m - 1] == 'O')
                dfs(board, i, m - 1);
        }

        // 从上边和下边向中间遍历
        for (int j = 0; j < m; j++)
        {
            if (board[0][j] == 'O')
                dfs(board, 0, j);
            if (board[n - 1][j] == 'O')
                dfs(board, n - 1, j);
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                if (board[i][j] == 'A')
                    board[i][j] = 'O';
            }
        }
    }
};

int main()
{
    vector<vector<vector<char>>> boards = {
        {
            {'X', 'X', 'X', 'X'},
            {'X', 'O', 'O', 'X'},
            {'X', 'X', 'O', 'X'},
            {'X', 'O', 'X', 'X'},
        },
        {
            {'X'},
        },
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    s.solve(boards[group]);
    output2d(boards[group]);

    return 0;
}
