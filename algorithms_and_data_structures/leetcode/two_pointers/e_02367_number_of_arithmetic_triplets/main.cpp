#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int arithmeticTriplets(vector<int> &nums, int diff)
    {
        int tableSize = nums[nums.size() - 1] + diff * 2;
        bool table[tableSize];

        for (int i = 0; i < tableSize; i++)
            table[i] = false;

        for (int i = 0; i < nums.size(); i++)
            table[nums[i]] = true;

        int count = 0;
        for (int i = 0; i < nums.size() - 2; i++)
        {
            if (table[nums[i] + diff] && table[nums[i] + diff * 2])
                count++;
        }

        return count;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {0, 1, 4, 6, 7, 10}, // 2
        {4, 5, 6, 7, 8, 9},  // 2
    };
    vector<int> diffs = {3, 2};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.arithmeticTriplets(nums[group], diffs[group]) << endl;

    return 0;
}
