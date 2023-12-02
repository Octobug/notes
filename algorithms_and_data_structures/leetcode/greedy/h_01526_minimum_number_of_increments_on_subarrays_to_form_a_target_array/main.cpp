#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int minNumberOperations(vector<int> &target)
    {
        int result = target[0];
        for (int i = 1; i < target.size(); i++)
        {
            if (target[i] > target[i - 1])
                result += target[i] - target[i - 1];
        }
        return result;
    }
};

int main()
{
    vector<vector<int>> targets = {
        {1, 2, 3, 2, 1}, // 3
        {3, 1, 1, 2},    // 4
        {3, 1, 5, 4, 2}, // 7
    };

    int group = getGroup();
    Solution s;
    cout << s.minNumberOperations(targets[group]) << endl;

    return 0;
}
