#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
    static bool cmp(vector<int> &a, vector<int> &b)
    {
        if (a[0] == b[0])
            return a[1] < b[1];

        return a[0] < b[0];
    }

public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end(), cmp);

        vector<vector<int>> result;

        int left = intervals[0][0];
        int right = intervals[0][1];

        for (int i = 1; i < intervals.size(); i++)
        {
            if (intervals[i][0] <= right)
            {
                right = max(right, intervals[i][1]);
            }
            else
            {
                result.push_back({left, right});
                left = intervals[i][0];
                right = intervals[i][1];
            }
        }
        result.push_back({left, right});

        return result;
    }
};

int main()
{
    vector<vector<vector<int>>> inputs = {
        {{1, 3}, {2, 6}, {8, 10}, {15, 18}},
        {{1, 4}, {4, 5}},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<int>> result = s.merge(inputs[group]);
    output2d(result);

    return 0;
}
