#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "array.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    vector<int> findingUsersActiveMinutes(vector<vector<int>> &logs, int k)
    {
        unordered_map<int, unordered_set<int>> usersTimes;
        for (int i = 0; i < logs.size(); i++)
            usersTimes[logs[i][0]].insert(logs[i][1]);

        vector<int> result(k, 0);
        for (auto const &user : usersTimes)
            result[user.second.size() - 1]++;

        return result;
    }
};

int main()
{
    vector<vector<vector<int>>> logs = {
        {
            {0, 5},
            {1, 2},
            {0, 2},
            {0, 5},
            {1, 3},
        }, // [0,2,0,0,0]
        {
            {1, 1},
            {2, 2},
            {2, 3},
        }, // [1,1,0,0]
    };
    vector<int> ks = {5, 4};
    int group = getGroup();

    Solution s;
    vector<int> result = s.findingUsersActiveMinutes(logs[group], ks[group]);
    output(result);

    return 0;
}
