#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class SolutionU
{
public:
    vector<vector<int>> result;
    vector<int> path;

    void dfs(vector<vector<int>> &graph, int index)
    {
        path.push_back(index);
        if (index == (graph.size() - 1))
        {
            result.push_back(path);
            return;
        }

        for (int i = 0; i < graph[index].size(); i++)
        {
            dfs(graph, graph[index][i]);
            path.pop_back();
        }
    }

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
    {
        dfs(graph, 0);
        return result;
    }
};

class Solution
{
public:
    vector<vector<int>> result;
    vector<int> path;

    void dfs(vector<vector<int>> &graph, int index)
    {
        if (index == (graph.size() - 1))
        {
            result.push_back(path);
            return;
        }

        for (int i = 0; i < graph[index].size(); i++)
        {
            path.push_back(graph[index][i]);
            dfs(graph, graph[index][i]);
            path.pop_back();
        }
    }

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
    {
        path.push_back(0);
        dfs(graph, 0);
        return result;
    }
};

int main()
{
    vector<vector<vector<int>>> graphs = {
        {
            {1, 2},
            {3},
            {3},
            {},
        }, // [[0,1,3],[0,2,3]]
        {
            {4, 3, 1},
            {3, 2, 4},
            {3},
            {4},
            {},
        }, // [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<int>> result = s.allPathsSourceTarget(graphs[group]);
    output2d(result);

    return 0;
}
