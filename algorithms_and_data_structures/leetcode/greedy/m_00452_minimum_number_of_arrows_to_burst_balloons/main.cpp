#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
    static bool cmp(const vector<int> &a, const vector<int> &b)
    {
        if (a[0] == b[0])
            return a[1] < b[1];
        return a[0] < b[0];
    }

public:
    int findMinArrowShots(vector<vector<int>> &points)
    {
        sort(points.begin(), points.end(), cmp);

        int count = points.size();
        int rightBorder = points[0][1];

        for (int i = 1; i < points.size(); i++)
        {
            if (points[i][0] <= rightBorder)
            {
                count--;
                rightBorder = min(rightBorder, points[i][1]);
            }
            else
                rightBorder = points[i][1];
        }

        return count;
    }
};

int main()
{
    vector<vector<vector<int>>> inputs = {
        {{10, 16}, {2, 8}, {1, 6}, {7, 12}},                          // 2
        {{1, 2}, {3, 4}, {5, 6}, {7, 8}},                             // 4
        {{1, 2}, {2, 3}, {3, 4}, {4, 5}},                             // 2
        {{9, 12}, {1, 10}, {4, 11}, {8, 12}, {3, 9}, {6, 9}, {6, 7}}, // 2
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.findMinArrowShots(inputs[group]) << endl;

    return 0;
}
