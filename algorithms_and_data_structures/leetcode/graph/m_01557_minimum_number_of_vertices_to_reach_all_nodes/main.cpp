#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>> &edges)
    {
        bool table[n];

        for (int i = 0; i < n; i++)
            table[i] = false;

        for (int i = 0; i < edges.size(); i++)
            table[edges[i][1]] = true;

        vector<int> result(n, 0);
        int count = 0;

        for (int i = 0; i < n; i++)
        {
            if (!table[i])
                result[count++] = i;
        }

        result.resize(count);
        return result;
    }
};

int main()
{
    vector<int> ns = {
        6, // [0,3]
        5, // [0,2,3]
    };
    vector<vector<vector<int>>> edges = {
        {
            {0, 1},
            {0, 2},
            {2, 5},
            {3, 4},
            {4, 2},
        },
        {
            {0, 1},
            {2, 1},
            {3, 1},
            {1, 4},
            {2, 4},
        },
    };

    int group;
    cout << "Please enter group: ";
    cin >> group;
    group--;

    Solution s;
    vector<int> result = s.findSmallestSetOfVertices(ns[group], edges[group]);
    output(result);

    return 0;
}
