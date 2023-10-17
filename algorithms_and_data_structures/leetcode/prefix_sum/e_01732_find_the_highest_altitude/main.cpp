#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int largestAltitude(vector<int> &gain)
    {
        int result = 0;
        int gained = 0;

        for (int i = 0; i < gain.size(); i++)
        {
            gained += gain[i];
            result = max(result, gained);
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> gains = {
        {-5, 1, 5, 0, -7},         // 1
        {-4, -3, -2, -1, 4, 3, 2}, // 0
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.largestAltitude(gains[group]) << endl;

    return 0;
}
