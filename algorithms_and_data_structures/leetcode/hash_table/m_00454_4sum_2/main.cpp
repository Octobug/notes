#include <iostream>
#include <unordered_map>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3, vector<int> &nums4)
    {
        unordered_map<int, int> umap;
        for (int a : nums1)
        {
            for (int b : nums2)
            {
                umap[a + b]++;
            }
        }

        int count = 0;
        for (int c : nums3)
        {
            for (int d : nums4)
            {
                int complement = -c - d;
                if (umap.count(complement))
                {
                    count += umap[complement];
                }
            }
        }

        return count;
    }
};

int main()
{
    vector<vector<vector<int>>> groups = {
        {
            {1, 2},
            {-2, -1},
            {-1, 2},
            {0, 2},
        },
        {
            {0},
            {0},
            {0},
            {0},
        },
        {
            {-1, -1},
            {-1, 1},
            {-1, 1},
            {1, -1},
        }};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.fourSumCount(
                groups[group][0], groups[group][1],
                groups[group][2], groups[group][3])
         << endl;

    return 0;
}
