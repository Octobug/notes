#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>> &grid)
    {
        int len = grid.size();
        vector<int> rowMaxes(len, 0);
        vector<int> colMaxes(len, 0);

        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
            {
                rowMaxes[j] = max(rowMaxes[j], grid[i][j]);
                colMaxes[i] = max(colMaxes[i], grid[i][j]);
            }
        }

        int result = 0;

        for (int i = 0; i < len; i++)
            for (int j = 0; j < len; j++)
                result += (min(rowMaxes[j], colMaxes[i]) - grid[i][j]);

        return result;
    }
};

int main()
{
    vector<vector<vector<int>>> grids = {
        {
            {3, 0, 8, 4},
            {2, 4, 5, 7},
            {9, 2, 6, 3},
            {0, 3, 1, 0},
        }, // 35
        {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
        }, // 0
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maxIncreaseKeepingSkyline(grids[group]) << endl;

    return 0;
}
