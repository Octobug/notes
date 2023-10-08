#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int findCenter(vector<vector<int>> &edges)
    {
        if (edges[0][0] == edges[1][0] || edges[0][0] == edges[1][1])
            return edges[0][0];
        else
            return edges[0][1];
    }
};

int main()
{
    vector<vector<vector<int>>> edges = {
        {
            {1, 2},
            {2, 3},
            {4, 2},
        }, // 2
        {
            {1, 2},
            {5, 1},
            {1, 3},
            {1, 4},
        }, // 1
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.findCenter(edges[group]) << endl;

    return 0;
}
