#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> executeInstructions(int n, vector<int> &startPos, string s)
    {
        int len = s.size();
        vector<int> result(len, 0);

        for (int i = 0; i < len; i++)
        {
            int offsetX = startPos[0], offsetY = startPos[1];
            for (int j = i; j < len; j++)
            {
                if (s[j] == 'U')
                    offsetX--;
                else if (s[j] == 'D')
                    offsetX++;
                else if (s[j] == 'L')
                    offsetY--;
                else
                    offsetY++;

                if (offsetX < 0 || offsetX >= n || offsetY < 0 || offsetY >= n)
                    break;

                result[i]++;
            }
        }

        return result;
    }
};

int main()
{
    vector<int> ns = {
        3, // [1,5,4,3,1,0]
        2, // [4,1,0,0]
        1, // [0,0,0,0]
    };
    vector<vector<int>> startPoses = {
        {0, 1},
        {1, 1},
        {0, 0},
    };
    vector<string> ss = {
        "RRDDLU",
        "LURD",
        "LRUD",
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<int> result = s.executeInstructions(
        ns[group], startPoses[group], ss[group]);

    output(result);

    return 0;
}
