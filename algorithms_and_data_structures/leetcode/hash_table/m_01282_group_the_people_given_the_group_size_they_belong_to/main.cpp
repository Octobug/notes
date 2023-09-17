#include <iostream>
#include <unordered_map>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<vector<int>> groupThePeople(vector<int> &groupSizes)
    {
        vector<vector<int>> result;
        unordered_map<int, vector<int>> umap;

        for (int i = 0; i < groupSizes.size(); i++)
        {
            if (umap.find(groupSizes[i]) == umap.end())
                umap[groupSizes[i]] = vector<int>(groupSizes[i], 0);
        }

        for (int i = 0; i < groupSizes.size(); i++)
        {
            int num = groupSizes[i];
            int count = umap[num][num - 1];
            if (count == num - 1)
            {
                umap[num][num - 1] = i;
                result.push_back(umap[num]);
                umap[num][num - 1] = 0;
            }
            else
            {
                umap[num][num - 1]++;
                umap[num][count] = i;
            }
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> gss = {
        {3, 3, 3, 3, 3, 1, 3}, // [5],[0,1,2],[3,4,6]
        {2, 1, 3, 3, 3, 2},    // [1],[0,5],[2,3,4]
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<int>> result = s.groupThePeople(gss[group]);
    output2d(result);

    return 0;
}
