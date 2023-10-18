#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maximum69Number(int num)
    {
        int bits[4] = {1000, 100, 10, 1};
        int temp = num;

        for (int i = 0; i < 4; i++)
        {
            if (temp < bits[i])
                continue;

            if (temp / bits[i] == 6)
            {
                num += bits[i] * 3;
                return num;
            }
            temp -= temp / bits[i] * bits[i];
        }

        return num;
    }
};

int main()
{
    vector<int> nums = {
        9669, // 9969
        9996, // 9999
        9999, // 9999
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maximum69Number(nums[group]) << endl;

    return 0;
}
