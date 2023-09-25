#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> createTargetArray(vector<int> &nums, vector<int> &index)
    {
        int len = nums.size();
        vector<int> result(len);

        for (int i = 1; i < len; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (index[i] <= index[j])
                    index[j]++;
            }
        }

        for (int i = 0; i < len; i++)
            result[index[i]] = nums[i];

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {0, 1, 2, 3, 4}, // [0,4,1,3,2]
        {1, 2, 3, 4, 0}, // [0,1,2,3,4]
        {1},             // [1]
    };
    vector<vector<int>> indexs = {
        {0, 1, 2, 2, 1},
        {0, 1, 2, 3, 0},
        {0},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<int> result = s.createTargetArray(nums[group], indexs[group]);

    output(result);

    return 0;
}
