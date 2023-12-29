#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int countTestedDevices(vector<int> &batteryPercentages)
    {
        int result = 0;
        for (int i = 0; i < batteryPercentages.size(); i++)
        {
            if (batteryPercentages[i] > result)
                result++;
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> batteryPercentages = {
        {1, 1, 2, 1, 3}, // 3
        {0, 1, 2},       // 2
    };

    int group = getGroup();

    Solution s;
    cout << s.countTestedDevices(batteryPercentages[group]) << endl;

    return 0;
}
