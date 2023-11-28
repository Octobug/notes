#include <iostream>
#include <vector>
#include <queue>
#include "array.h"
#include "input.h"

using namespace std;

class Graph1
{
public:
    Graph1(int n, vector<vector<int>> &edges)
    {
        this->n = n;
        graph = vector<vector<pair<int, int>>>(n);
        for (auto &edge : edges)
            addEdge(edge);
    }

    void addEdge(vector<int> edge)
    {
        graph[edge[0]].push_back({edge[1], edge[2]});
    }

    int shortestPath(int node1, int node2)
    {
        vector<int> costs(n, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // {cost, node}
        costs[node1] = 0;
        pq.push({0, node1});

        while (!pq.empty())
        {
            auto [curr_cost, curr_node] = pq.top();
            pq.pop();
            for (auto [next_node, next_cost] : graph[curr_node])
            {
                int cost = curr_cost + next_cost;
                if (cost < costs[next_node])
                {
                    costs[next_node] = cost;
                    pq.push({cost, next_node});
                }
            }
        }

        if (costs[node2] == INT_MAX)
            return -1;
        return costs[node2];
    }

private:
    int n;
    vector<vector<pair<int, int>>> graph; // graph[from] = {to, cost}
};

class Graph
{
    static const int N = 101;
    int adj[N][N];
    int n;
    int COST_MAX = 10e6;

public:
    Graph(int n, vector<vector<int>> &edges)
    {
        this->n = n;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                adj[i][j] = COST_MAX;

            adj[i][i] = 0;
        }

        for (auto &edge : edges)
            adj[edge[0]][edge[1]] = edge[2];

        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                    adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }

    void addEdge(vector<int> edge)
    {
        int u = edge[0], v = edge[1], cost = edge[2];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                adj[i][j] = min(adj[i][j], adj[i][u] + adj[v][j] + cost);
        }
    }

    int shortestPath(int node1, int node2)
    {
        return adj[node1][node2] == COST_MAX ? -1 : adj[node1][node2];
    }
};

int main()
{
    vector<vector<int>> edges = {
        {0, 2, 5},
        {0, 1, 2},
        {1, 2, 1},
        {3, 0, 3},
    };

    Graph *g = new Graph(4, edges);
    cout << g->shortestPath(3, 2) << endl; // 6
    cout << g->shortestPath(0, 3) << endl; // -1
    g->addEdge({1, 3, 4});
    cout << g->shortestPath(0, 3) << endl; // 6
    return 0;
}
