#include <iostream>
#include <vector>
#include "array.h"

class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        int total = m * n;
        vector<int> result(total, 0);
        vector<vector<int>> inc_direc = {
            {0, 1},
            {1, 0},
            {0, -1},
            {-1, 0}};
        int direc = 0;
        int r_inc = inc_direc[direc][0];
        int c_inc = inc_direc[direc][1];

        int index = 0;
        int row = 0;
        int col = 0;
        while (index < total)
        {
            while (col < n && col >= 0 && row < m && row >= 0 && matrix[row][col] < 101)
            {
                result[index] = matrix[row][col];
                matrix[row][col] = 101;
                row += r_inc;
                col += c_inc;
                index++;
            }

            row -= r_inc;
            col -= c_inc;
            direc = (direc + 1) % 4;
            r_inc = inc_direc[direc][0];
            c_inc = inc_direc[direc][1];
            row += r_inc;
            col += c_inc;
        }

        return result;
    }
};

int main()
{
    int m, n;
    cout << "Please input m: ";
    cin >> m;
    cout << "Please input n: ";
    cin >> n;

    vector<vector<int>> matrix(m, vector<int>(n, 0));
    int num = 1;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = num++;
        }
    }

    Solution s;
    vector<int> result = s.spiralOrder(matrix);
    output(result);
    return 0;
}
