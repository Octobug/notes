#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<vector<int>> findMatrix(vector<int> &nums)
    {
        int len = nums.size();
        int table[len + 1];

        for (int i = 0; i <= len; i++)
            table[i] = 0;

        for (int i = 0; i < len; i++)
            table[nums[i]]++;

        vector<vector<int>> result;

        for (int i = 0; i <= len; i++)
        {
            for (int j = 0; j < table[i]; j++)
            {
                if (result.size() == j)
                    result.push_back(vector<int>());

                result[j].push_back(i);
            }
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {1, 3, 4, 1, 2, 3, 1}, // 3
        {1, 2, 3, 4},          // 1
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<int>> result = s.findMatrix(nums[group]);
    output2d(result);

    return 0;
}
