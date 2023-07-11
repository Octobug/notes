#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int monotoneIncreasingDigits(int n)
    {
        string sn = to_string(n);

        for (int i = sn.size() - 1; i > 0; i--)
        {
            if (sn[i - 1] > sn[i])
            {
                sn[i - 1]--;
                sn[i] = '9';
            }
        }

        for (int i = 0; i < sn.size() - 1; i++)
        {
            if (sn[i] > sn[i + 1])
                sn[i + 1] = '9';
        }

        return stoi(sn);
    }
};

int main()
{
    vector<int> inputs = {10, 1234, 332, 3465, 100};
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.monotoneIncreasingDigits(inputs[group]) << endl;

    return 0;
}
