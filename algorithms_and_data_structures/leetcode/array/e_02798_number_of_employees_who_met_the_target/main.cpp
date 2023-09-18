#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int numberOfEmployeesWhoMetTarget(vector<int> &hours, int target)
    {
        int count = 0;
        for (int i = 0; i < hours.size(); i++)
            if (hours[i] >= target)
                count++;

        return count;
    }
};

int main()
{
    vector<vector<int>> hours = {
        {0, 1, 2, 3, 4}, // 3
        {5, 1, 4, 2, 2}, // 0
    };
    vector<int> targets = {2, 6};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.numberOfEmployeesWhoMetTarget(hours[group], targets[group]) << endl;

    return 0;
}
