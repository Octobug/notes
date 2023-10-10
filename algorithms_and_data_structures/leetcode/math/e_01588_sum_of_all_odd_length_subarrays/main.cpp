#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int sumOddLengthSubarrays(vector<int> &arr)
    {
        int sum = 0;
        int len = arr.size();

        vector<int> timesTable(len, 0);

        int calLimit = (len + 1) / 2;
        int total = len + 1;

        for (int i = 0; i < calLimit; i++)
        {
            for (int j = 1; j <= len; j += 2)
                timesTable[i] += min(j, min(i + 1, total - j));
        }

        for (int i = len - 1; i >= calLimit; i--)
            timesTable[i] = timesTable[len - i - 1];

        for (int i = 0; i < len; i++)
            sum += arr[i] * timesTable[i];

        return sum;
    }
};

int main()
{
    vector<vector<int>> arrs = {
        {1, 4, 2, 5, 3},                   // 58
        {1, 2},                            // 3
        {10, 11, 12},                      // 66
        {7, 6, 8, 6},                      // 68
        {6, 9, 14, 5, 3, 8, 7, 12, 13, 1}, // 878
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.sumOddLengthSubarrays(arrs[group]) << endl;

    return 0;
}
