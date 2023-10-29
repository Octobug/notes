#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int sumCounts(vector<int> &nums)
    {
        int len = nums.size();
        int result = len;
        int table[101] = {0};

        for (int i = 2; i <= len; i++)
        {
            int count = 0;
            for (int k = 0; k < i; k++)
            {
                if (table[nums[k]] == 0)
                    count++;

                table[nums[k]]++;
            }
            result += count * count;

            for (int j = 1; j <= len - i; j++)
            {
                table[nums[j - 1]]--;
                if (table[nums[j - 1]] == 0)
                    count--;

                if (table[nums[j + i - 1]] == 0)
                    count++;
                table[nums[j + i - 1]]++;

                result += count * count;
            }

            for (int k = len - i; k < len; k++)
                table[nums[k]] = 0;
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {1, 2, 1},    // 15
        {1, 1},       // 3
        {2, 2, 5, 5}, // 22
    };

    int group;
    cout << "Please enter group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.sumCounts(nums[group]) << endl;

    return 0;
}
