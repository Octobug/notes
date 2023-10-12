#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<vector<int>> largestLocal(vector<vector<int>> &grid)
    {
        int len = grid.size();
        vector<vector<int>> result(len - 2, vector<int>(len - 2, 0));

        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
            {
                for (int k = -1; k < 2; k++)
                {
                    int r = i + k;
                    if (r < 1 || r >= len - 1)
                        continue;

                    r--;
                    for (int l = -1; l < 2; l++)
                    {
                        int c = j + l;
                        if (c < 1 || c >= len - 1)
                            continue;

                        c--;
                        result[r][c] = max(result[r][c], grid[i][j]);
                    }
                }
            }
        }

        return result;
    }
};

int main()
{
    vector<vector<vector<int>>> grids = {
        {
            {9, 9, 8, 1},
            {5, 6, 2, 6},
            {8, 2, 6, 4},
            {6, 2, 2, 2},
        }, // [[9,9],[8,6]]
        {
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 2, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
        }, // [[2,2,2],[2,2,2],[2,2,2]]
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<int>> result = s.largestLocal(grids[group]);
    output2d(result);

    return 0;
}
