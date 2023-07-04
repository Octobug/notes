#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<vector<string>> result;
    vector<pair<int, int>> points;
    bool cols[9] = {0};

    bool isCollide(int n, int row, int col)
    {
        if (cols[col])
            return true;

        for (int i = 0; i < points.size(); i++)
            if (abs(row - points[i].first) == abs(col - points[i].second))
                return true;

        return false;
    }

    vector<string> getChessboard()
    {
        vector<string> result(points.size(), string(points.size(), '.'));
        for (int i = 0; i < points.size(); i++)
            result[points[i].first][points[i].second] = 'Q';

        return result;
    }

    void backtrack(int n, int row)
    {
        if (row == n)
        {
            result.push_back(getChessboard());
            return;
        }

        for (int col = 0; col < n; col++)
        {
            if (isCollide(n, row, col))
                continue;

            points.push_back({row, col});
            cols[col] = true;

            backtrack(n, row + 1);

            points.pop_back();
            cols[col] = false;
        }
    }

    vector<vector<string>> solveNQueens(int n)
    {
        backtrack(n, 0);
        return result;
    }
};

int main()
{
    int n;
    cout << "Please input n: ";
    cin >> n;

    Solution s;
    vector<vector<string>> result = s.solveNQueens(n);
    output2d(result);

    return 0;
}
