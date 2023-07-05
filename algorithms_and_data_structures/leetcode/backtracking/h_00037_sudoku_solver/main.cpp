#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    bool isValid(vector<vector<char>> &board, int row, int col, char val)
    {
        for (int i = 0; i < 9; i++)
            if (board[row][i] == val)
                return false;

        for (int j = 0; j < 9; j++)
            if (board[j][col] == val)
                return false;

        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = startRow; i < startRow + 3; i++)
            for (int j = startCol; j < startCol + 3; j++)
                if (board[i][j] == val)
                    return false;

        return true;
    }

    bool backtrack(vector<vector<char>> &board, int idBegin)
    {
        for (int id = idBegin; id < 81; id++)
        {
            int i = id / 9;
            int j = id % 9;
            if (board[i][j] != '.')
                continue;

            for (char num = '1'; num <= '9'; num++)
            {
                if (!isValid(board, i, j, num))
                    continue;

                board[i][j] = num;

                if (backtrack(board, id + 1))
                    return true;

                board[i][j] = '.';
            }
            return false;
        }
        return true;
    }

    void solveSudoku(vector<vector<char>> &board)
    {
        backtrack(board, 0);
    }
};

int main()
{
    vector<vector<vector<char>>> inputs = {
        {
            {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'},
        },
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<char>> board = inputs[group];
    s.solveSudoku(board);
    output2d(board);

    return 0;
}
