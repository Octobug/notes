#include <iostream>
#include <vector>
#include <string>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> smallerNumbersThanCurrent(vector<int> &nums)
    {
        vector<int> result(nums.size(), 0);
        int NUM_SET_LEN = 102;
        int count[NUM_SET_LEN];

        for (int i = 0; i < NUM_SET_LEN; i++)
            count[i] = 0;

        for (int i = 0; i < nums.size(); i++)
            count[nums[i] + 1]++;

        for (int i = 1; i < NUM_SET_LEN; i++)
            count[i] += count[i - 1];

        for (int i = 0; i < nums.size(); i++)
            result[i] = count[nums[i]];

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {8, 1, 2, 2, 3},      // 4,0,1,1,3
        {6, 5, 4, 8},         // 2,1,0,3
        {7, 7, 7, 7},         // 0,0,0,0
        {5, 0, 10, 0, 10, 6}, // 2,0,4,0,4,3
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<int> result = s.smallerNumbersThanCurrent(nums[group]);
    output(result);
}
