#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int diagonalSum(vector<vector<int>> &mat)
    {
        int len = mat.size();
        int sum = 0;

        if (len % 2 != 0)
            sum = -mat[len / 2][len / 2];

        for (int i = 0, j = 0; i < len; i++, j++)
            sum += mat[i][j];

        for (int i = 0, j = len - 1; i < len; i++, j--)
            sum += mat[i][j];

        return sum;
    }
};

int main()
{
    vector<vector<vector<int>>> mats = {
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
        }, // 25
        {
            {1, 1, 1, 1},
            {1, 1, 1, 1},
            {1, 1, 1, 1},
            {1, 1, 1, 1},
        }, // 8
        {
            {5},
        }, // 5
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.diagonalSum(mats[group]) << endl;

    return 0;
}
