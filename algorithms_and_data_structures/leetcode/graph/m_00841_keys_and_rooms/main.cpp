#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<bool> visited;

    void dfs(vector<vector<int>> &rooms, int index)
    {
        visited[index] = true;

        for (int i = 0; i < rooms[index].size(); i++)
        {
            if (!visited[rooms[index][i]])
                dfs(rooms, rooms[index][i]);
        }
    }

    bool canVisitAllRooms(vector<vector<int>> &rooms)
    {
        visited = vector<bool>(rooms.size(), false);

        dfs(rooms, 0);

        for (int i = 0; i < visited.size(); i++)
            if (!visited[i])
                return false;

        return true;
    }
};

int main()
{
    vector<vector<vector<int>>> rooms = {
        {
            {1},
            {2},
            {3},
            {},
        }, // 1
        {
            {1, 3},
            {3, 0, 1},
            {2},
            {0},
        }, // 0
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.canVisitAllRooms(rooms[group]) << endl;

    return 0;
}
