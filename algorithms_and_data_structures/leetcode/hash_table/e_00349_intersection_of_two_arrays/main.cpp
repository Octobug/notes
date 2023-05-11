#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        int table[1001] = {0};
        vector<int> result;

        for (int i = 0; i < nums1.size(); i++)
        {
            table[nums1[i]]++;
        }

        for (int i = 0; i < nums2.size(); i++)
        {
            if (table[nums2[i]] > 0)
            {
                result.push_back(nums2[i]);
                table[nums2[i]] = 0;
            }
        }

        return result;
    }
};

int main()
{
    vector<int> numsA1 = {1, 2, 2, 1};
    vector<int> numsA2 = {2, 2};
    vector<int> numsB1 = {4, 9, 5};
    vector<int> numsB2 = {9, 4, 9, 8, 4};

    vector<vector<int>> groups1 = {numsA1, numsB1};
    vector<vector<int>> groups2 = {numsA2, numsB2};

    int group;
    cout << "Please input group: ";
    cin >> group;

    Solution s;
    vector<int> result = s.intersection(groups1[group - 1], groups2[group - 1]);
    output(result);

    return 0;
}
