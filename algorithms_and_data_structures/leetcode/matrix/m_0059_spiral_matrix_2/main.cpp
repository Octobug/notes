#include <iostream>
#include <vector>
#include "array.h"

class Solution
{
public:
    vector<vector<int>> generateMatrix(int n)
    {
        int limit = n * n;
        vector<vector<int>> result(n, vector<int>(n, 0));
        vector<vector<int>> inc_direc = {
            {0, 1},
            {1, 0},
            {0, -1},
            {-1, 0}};
        int direc = 0;
        int r_inc = inc_direc[direc][0];
        int c_inc = inc_direc[direc][1];

        int num = 0;
        int row = 0;
        int col = 0;
        while (num < limit)
        {
            while (col < n && col >= 0 && row < n && row >= 0 && !result[row][col])
            {
                result[row][col] = ++num;
                row += r_inc;
                col += c_inc;
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
    int n;
    cout << "Please input n: ";
    cin >> n;
    Solution s;
    vector<vector<int>> result = s.generateMatrix(n);
    output2d(result);
    return 0;
}
