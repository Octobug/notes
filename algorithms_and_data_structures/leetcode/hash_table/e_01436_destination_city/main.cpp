#include <iostream>
#include <unordered_set>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    string destCity(vector<vector<string>> &paths)
    {
        unordered_set<string> uset;
        for (int i = 0; i < paths.size(); i++)
            uset.insert(paths[i][0]);

        for (int i = 0; i < paths.size(); i++)
            if (uset.find(paths[i][1]) == uset.end())
                return paths[i][1];

        return "";
    }
};

int main()
{
    vector<vector<vector<string>>> paths = {
        {
            {"London", "New York"},
            {"New York", "Lima"},
            {"Lima", "Sao Paulo"},
        }, // "Sao Paulo"
        {
            {"B", "C"},
            {"D", "B"},
            {"C", "A"},
        }, // "A"
        {
            {"A", "Z"},
        }, // "Z"
    };

    int group = getGroup();

    Solution s;
    cout << s.destCity(paths[group]) << endl;

    return 0;
}
