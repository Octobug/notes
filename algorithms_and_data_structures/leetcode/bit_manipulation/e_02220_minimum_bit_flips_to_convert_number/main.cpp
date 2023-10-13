#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int minBitFlips(int start, int goal)
    {
        int count = 0;

        while (start > 0 || goal > 0)
        {
            if (start % 2 != goal % 2)
                count++;

            start /= 2;
            goal /= 2;
        }

        return count;
    }
};

int main()
{
    vector<int> starts = {
        10, // 3
        3,  // 3
        10, // 3
    };
    vector<int> goals = {7, 4, 82};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.minBitFlips(starts[group], goals[group]) << endl;

    return 0;
}
