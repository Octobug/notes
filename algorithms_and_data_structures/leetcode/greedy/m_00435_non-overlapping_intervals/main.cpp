#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{

    static bool cmp(const vector<int> &a, const vector<int> &b)
    {
        return a[1] < b[1];
    }

public:
    int eraseOverlapIntervals(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end(), cmp);

        int nonOverlap = 1;
        int rightBorder = intervals[0][1];

        for (int i = 1; i < intervals.size(); i++)
        {
            if (intervals[i][0] >= rightBorder)
            {
                nonOverlap++;
                rightBorder = intervals[i][1];
            }
        }

        return intervals.size() - nonOverlap;
    }
};

int main()
{
    vector<vector<vector<int>>> inputs = {
        {{1, 2}, {2, 3}, {3, 4}, {1, 3}}, // 1
        {{1, 2}, {1, 2}, {1, 2}},         // 2
        {{1, 2}, {2, 3}},                 // 0
        {
            {-52, 31},
            {-73, -26},
            {82, 97},
            {-65, -11},
            {-62, -49},
            {95, 99},
            {58, 95},
            {-31, 49},
            {66, 98},
            {-63, 2},
            {30, 47},
            {-40, -26},
        },                                        // 7
        {{1, 2}, {2, 3}, {3, 4}, {1, 3}, {2, 5}}, // 2
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.eraseOverlapIntervals(inputs[group]) << endl;

    return 0;
}
