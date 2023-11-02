#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int countPoints(string rings)
    {
        int table[10] = {0};
        for (int i = 0, j = 1; i < rings.size(); i += 2, j += 2)
        {
            if (rings[i] == 'B')
                table[rings[j] - '0'] |= 1;
            else if (rings[i] == 'G')
                table[rings[j] - '0'] |= 2;
            else
                table[rings[j] - '0'] |= 4;
        }

        int result = 0;
        for (int i = 0; i < 10; i++)
            if (table[i] == 7)
                result++;

        return result;
    }
};

int main()
{
    vector<string> rings = {
        "B0B6G0R6R0R6G9", // 1
        "B0R0G0R9R0B0G0", // 1
        "G4",             // 0
    };

    int group;
    cout << "Please enter group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.countPoints(rings[group]) << endl;

    return 0;
}
