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
        for (int i = 0; i < disjoint.size(); ++i)
            disjoint[i] = i;
    }

    int find(int u)
    {
        if (u == disjoint[u])
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

        disjoint[v] = u;
    }

    bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
    {
        disjoint = vector<int>(n, 0);
        init();

        for (int i = 0; i < edges.size(); i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            join(u, v);
        }

        return isSame(source, destination);
    }
};

int main()
{
    vector<vector<vector<int>>> edges = {
        {
            {0, 1},
            {1, 2},
            {2, 0},
        }, // 1
        {
            {0, 1},
            {0, 2},
            {3, 5},
            {5, 4},
            {4, 3},
        }, // 0
    };
    vector<int> ns = {3, 6};
    vector<int> sources = {0, 0};
    vector<int> destins = {2, 5};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.validPath(ns[group], edges[group],
                        sources[group], destins[group])
         << endl;

    return 0;
}
