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
