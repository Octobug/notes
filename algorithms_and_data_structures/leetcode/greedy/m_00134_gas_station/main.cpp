#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int start = 0;
        int curSum = 0;
        int totalSum = 0;

        for (int i = 0; i < gas.size(); i++)
        {
            curSum += gas[i] - cost[i];
            totalSum += gas[i] - cost[i];

            if (curSum < 0)
            {
                start = i + 1;
                curSum = 0;
            }
        }

        if (totalSum < 0 || start == gas.size())
            return -1;

        return start;
    }
};

int main()
{
    vector<vector<vector<int>>> inputs = {
        {{1, 2, 3, 4, 5}, {3, 4, 5, 1, 2}},
        {{2, 3, 4}, {3, 4, 3}},
        {{5, 1, 2, 3, 4}, {4, 4, 1, 5, 1}},
        {{5, 8, 2, 8}, {6, 5, 6, 6}},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.canCompleteCircuit(inputs[group][0], inputs[group][1]) << endl;

    return 0;
}
