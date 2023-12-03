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
