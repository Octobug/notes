#include <iostream>
#include <unordered_map>
#include <vector>
#include "array.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    unordered_map<int, int> umap;

    vector<string> sortPeople(vector<string> &names, vector<int> &heights)
    {
        for (int i = 0; i < names.size(); i++)
            umap[heights[i]] = i;

        sort(heights.rbegin(), heights.rend());

        vector<string> result(names.size(), "");
        for (int i = 0; i < heights.size(); i++)
            result[i] = names[umap[heights[i]]];

        return result;
    }
};

int main()
{
    vector<vector<string>> names = {
        {"Mary", "John", "Emma"}, // ["Mary","Emma","John"]
        {"Alice", "Bob", "Bob"},  // ["Bob","Alice","Bob"]
    };

    vector<vector<int>> heights = {
        {180, 165, 170},
        {155, 185, 150},
    };

    int group = getGroup();
    Solution s;
    vector<string> result = s.sortPeople(names[group], heights[group]);
    output(result);

    return 0;
}
