#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int findDelayedArrivalTime(int arrivalTime, int delayedTime)
    {
        return (arrivalTime + delayedTime) % 24;
    }
};

int main()
{
    vector<int> arrivalTimes = {
        15, // 20
        13, // 0
    };
    vector<int> delayedTimes = {
        5,
        11,
    };

    int g = getGroup();

    Solution s;
    cout << s.findDelayedArrivalTime(arrivalTimes[g], delayedTimes[g]) << endl;

    return 0;
}
