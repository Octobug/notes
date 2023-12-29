#include <iostream>
#include <vector>
#include "array.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    vector<int> findIntersectionValues(vector<int> &nums1, vector<int> &nums2)
    {
        int r1 = 0, r2 = 0;
        int table[101] = {0};

        for (int i = 0; i < nums1.size(); i++)
            table[nums1[i]]++;

        for (int i = 0; i < nums2.size(); i++)
        {
            if (table[nums2[i]] != 0)
            {
                if (table[nums2[i]] > 0)
                {
                    r1 += table[nums2[i]];
                    table[nums2[i]] = -1;
                }
                r2++;
            }
        }

        return {r1, r2};
    }
};

int main()
{
    vector<vector<int>> nums1 = {
        {4, 3, 2, 3, 1}, // [3,4]
        {3, 4, 2, 3},    // [0,0]
    };
    vector<vector<int>> nums2 = {
        {2, 2, 5, 2, 3, 6},
        {1, 5},
    };

    int group = getGroup();
    Solution s;
    vector<int> result = s.findIntersectionValues(nums1[group], nums2[group]);
    output(result);

    return 0;
}
