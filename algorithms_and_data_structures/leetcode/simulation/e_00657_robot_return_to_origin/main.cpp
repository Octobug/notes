#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    bool judgeCircle(string moves)
    {
        int x = 0, y = 0;

        for (int i = 0; i < moves.size(); i++)
        {
            if (moves[i] == 'U')
                y++;
            else if (moves[i] == 'D')
                y--;
            else if (moves[i] == 'R')
                x++;
            else if (moves[i] == 'L')
                x--;
        }

        return x == 0 && y == 0;
    }
};

int main()
{
    vector<string> moves = {
        "UD", // 1
        "LL", // 0
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.judgeCircle(moves[group]) << endl;

    return 0;
}
