#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    void qsort(vector<vector<int>> &mat, int ra, int ca, int rb, int cb)
    {
        if (ra >= rb)
            return;

        swap(mat[ra][ca], mat[(ra + rb) / 2][(ca + cb) / 2]);

        int rlast, clast;
        rlast = ra;
        clast = ca;

        for (int ri = ra + 1, ci = ca + 1; ri <= rb; ri++, ci++)
        {
            if (mat[ri][ci] < mat[ra][ca])
            {
                rlast++;
                clast++;
                swap(mat[rlast][clast], mat[ri][ci]);
            }
        }

        swap(mat[ra][ca], mat[rlast][clast]);
        qsort(mat, ra, ca, rlast - 1, clast - 1);
        qsort(mat, rlast + 1, clast + 1, rb, cb);
    }

    vector<vector<int>> diagonalSort(vector<vector<int>> &mat)
    {
        int row = mat.size();
        int col = mat[0].size();
        int maxLen = min(row, col);

        for (int c = 0; c < col; c++)
        {
            int len = min(col - c, maxLen);
            int endr = len - 1;
            int endc = c + len - 1;
            qsort(mat, 0, c, endr, endc);
        }

        for (int r = 1; r < row; r++)
        {
            int len = min(row - r, maxLen);
            int endr = r + len - 1;
            int endc = len - 1;
            qsort(mat, r, 0, endr, endc);
        }

        return mat;
    }
};

int main()
{
    vector<vector<vector<int>>> mats = {
        {
            {3, 3, 1, 1},
            {2, 2, 1, 2},
            {1, 1, 1, 2},
        },
        {
            {11, 25, 66, 1, 69, 7},
            {23, 55, 17, 45, 15, 52},
            {75, 31, 36, 44, 58, 8},
            {22, 27, 33, 25, 68, 4},
            {84, 28, 14, 11, 5, 50},
        },
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<int>> result = s.diagonalSort(mats[group]);
    output2d(result);

    return 0;
}
