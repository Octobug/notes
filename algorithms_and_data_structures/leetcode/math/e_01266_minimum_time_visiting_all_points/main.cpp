#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int minTimeToVisitAllPoints(vector<vector<int>> &points)
    {
        int result = 0;

        for (int i = 1; i < points.size(); i++)
        {
            int dx = abs(points[i][0] - points[i - 1][0]);
            int dy = abs(points[i][1] - points[i - 1][1]);
            result += max(dx, dy);
        }

        return result;
    }
};

int main()
{
    vector<vector<vector<int>>> points = {
        {
            {1, 1},
            {3, 4},
            {-1, 0},
        }, // 7
        {
            {3, 2},
            {-2, 2},
        }, // 5
    };

    int group = getGroup();

    Solution s;
    cout << s.minTimeToVisitAllPoints(points[group]) << endl;

    return 0;
}
