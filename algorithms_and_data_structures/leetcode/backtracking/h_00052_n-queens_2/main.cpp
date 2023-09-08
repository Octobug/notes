#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int result = 0;

    vector<pair<int, int>> queens;
    bool cols[9] = {0};

    bool isCollide(int n, int row, int col)
    {
        if (cols[col])
            return true;

        for (int i = 0; i < queens.size(); i++)
            if (abs(row - queens[i].first) == abs(col - queens[i].second))
                return true;

        return false;
    }

    void backtrack(int n, int row)
    {
        if (row == n)
        {
            result++;
            return;
        }

        for (int col = 0; col < n; col++)
        {
            if (isCollide(n, row, col))
                continue;

            queens.push_back({row, col});
            cols[col] = true;

            backtrack(n, row + 1);

            queens.pop_back();
            cols[col] = false;
        }
    }

    int totalNQueens(int n)
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

    // n: 1, output: 1
    // n: 4, output: 2

    Solution s;
    cout << s.totalNQueens(n) << endl;

    return 0;
}
