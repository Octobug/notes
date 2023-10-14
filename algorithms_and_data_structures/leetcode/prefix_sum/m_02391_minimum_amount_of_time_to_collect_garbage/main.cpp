#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int garbageCollection(vector<string> &garbage, vector<int> &travel)
    {
        int result = 0;
        pair<int, int> ig = {0, 0}, im = {0, 0}, ip = {0, 0};
        pair<int, int> *pt;

        for (int i = 0; i < garbage.size(); i++)
        {
            for (int j = 0; j < garbage[i].size(); j++)
            {
                result++;

                if (garbage[i][j] == 'M')
                    pt = &im;
                else if (garbage[i][j] == 'P')
                    pt = &ip;
                else
                    pt = &ig;

                for (int v = pt->first; v < i; v++)
                    result += travel[v];

                *pt = {i, j};
            }
        }

        return result;
    }
};

int main()
{
    vector<vector<string>> garbages = {
        {"G", "P", "GP", "GG"}, // 21
        {"MMM", "PGM", "GP"},   // 37
    };
    vector<vector<int>> travels = {
        {2, 4, 3},
        {3, 10},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.garbageCollection(garbages[group], travels[group]) << endl;

    return 0;
}
