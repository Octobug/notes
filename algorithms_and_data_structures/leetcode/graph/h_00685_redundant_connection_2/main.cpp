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

    vector<int> findRedundantDirectedConnection(vector<vector<int>> &edges)
    {
        vector<int> indegrees(edges.size() + 1, -1);
        int edgeIndex1 = -1;
        int edgeIndex2 = -1;
        for (int i = 0; i < edges.size(); i++)
        {
            if (indegrees[edges[i][1]] != -1)
            {
                edgeIndex1 = indegrees[edges[i][1]];
                edgeIndex2 = i;
                break;
            }

            indegrees[edges[i][1]] = i;
        }

        disjoint = vector<int>(edges.size() + 1);
        init();

        for (int i = 0; i < edges.size(); i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];

            if (edgeIndex2 == i)
                continue;

            if (isSame(u, v))
            {
                if (edgeIndex2 == -1)
                    return edges[i];
                else
                    return edges[edgeIndex1];
            }

            join(v, u);
        }

        return edges[edgeIndex2];
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
            {4, 1},
            {1, 5},
        }, // [4,1]
        {
            {2, 1},
            {3, 1},
            {4, 2},
            {1, 4},
        }, // [2,1]
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<int> result = s.findRedundantDirectedConnection(edges[group]);
    output(result);

    return 0;
}
