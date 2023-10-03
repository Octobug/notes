#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> result;

        for (int i = 0; i < numRows; i++)
        {
            vector<int> nums(i + 1, 1);

            for (int j = 1; j < i; j++)
                nums[j] = result[i - 1][j - 1] + result[i - 1][j];

            result.push_back(nums);
        }

        return result;
    }
};

int main()
{
    int n;
    cout << "Please input n: ";
    cin >> n;

    Solution s;
    vector<vector<int>> result = s.generate(n);
    output2d(result);

    return 0;
}
