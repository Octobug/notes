#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    bool cmp(vector<int> &a, vector<int> &b)
    {
        return a[0] < b[0];
    }

    int maxWidthOfVerticalArea(vector<vector<int>> &points)
    {
        int result = 0;
        sort(points.begin(), points.end());

        for (int i = 1; i < points.size(); i++)
            result = max(result, points[i][0] - points[i - 1][0]);

        return result;
    }
};

int main()
{
    vector<vector<vector<int>>> points = {
        {
            {8, 7},
            {9, 9},
            {7, 4},
            {9, 7},
        }, // 1
        {
            {3, 1},
            {9, 0},
            {1, 0},
            {1, 4},
            {5, 3},
            {8, 8},
        }, // 3
    };

    int group;
    cout << "Pease input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maxWidthOfVerticalArea(points[group]) << endl;

    return 0;
}
