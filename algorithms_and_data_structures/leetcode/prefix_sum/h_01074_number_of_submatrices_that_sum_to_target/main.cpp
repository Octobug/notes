#include <iostream>
#include <vector>
#include "array.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    int numSubmatrixSumTarget(vector<vector<int>> &matrix, int target)
    {
        int m = matrix.size(), n = matrix[0].size();

        // calculate prefix sum for m
        for (int i = 0; i < m; i++)
        {
            for (int j = 1; j < n; j++)
                matrix[i][j] = matrix[i][j] + matrix[i][j - 1];
        }

        int count = 0, sum;
        unordered_map<int, int> counter;
        for (int colstart = 0; colstart < n; colstart++)
        {
            for (int col = colstart; col < n; col++)
            {
                counter.clear();
                counter[0] = 1;
                sum = 0;
                for (int row = 0; row < m; row++)
                {
                    sum += matrix[row][col];
                    if (colstart > 0)
                        sum -= matrix[row][colstart - 1];

                    if (counter.find(sum - target) != counter.end())
                        count += counter[sum - target];

                    counter[sum]++;
                }
            }
        }
        return count;
    }
};

int main()
{
    vector<vector<vector<int>>> matrices = {
        {
            {0, 1, 0},
            {1, 1, 1},
            {0, 1, 0},
        }, // 4
        {
            {1, -1},
            {-1, 1},
        }, // 5
        {
            {904},
        }, // 0
    };
    vector<int> targets = {0, 0, 0};

    int group = getGroup();
    Solution s;
    cout << s.numSubmatrixSumTarget(matrices[group], targets[group]) << endl;

    return 0;
}
