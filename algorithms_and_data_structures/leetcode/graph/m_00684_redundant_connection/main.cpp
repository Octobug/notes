#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> disjoint;

    void init()
    {
        for (int i = 0; i < disjoint.size(); i++)
            disjoint[i] = i;
    }

    int find(int u)
    {
        if (disjoint[u] == u)
            return u;
        else
            return disjoint[u] = find(disjoint[u]);
    }

    bool isSame(int u, int v)
    {
        u = find(u);
        v = find(v);

        return u == v;
    }

    void join(int u, int v)
    {
        u = find(u);
        v = find(v);

        if (u == v)
            return;
        else
            disjoint[v] = u;
    }

    vector<int> findRedundantConnection(vector<vector<int>> &edges)
    {
        disjoint = vector<int>(edges.size() + 1, 0);
        init();

        for (int i = 0; i < edges.size(); i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];

            if (isSame(u, v))
                return edges[i];
            else
                join(u, v);
        }

        return {};
    }
};

int main()
{
    vector<vector<vector<int>>> edges = {
        {
            {1, 2},
            {1, 3},
            {2, 3},
        }, // [2,3]
        {
            {1, 2},
            {2, 3},
            {3, 4},
            {1, 4},
            {1, 5},
        }, // [1,4]
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<int> result = s.findRedundantConnection(edges[group]);
    output(result);

    return 0;
}
