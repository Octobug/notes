#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int sumOfMultiples(int n)
    {
        bool table[n + 1];

        for (int i = 0; i <= n; i++)
            table[i] = false;

        for (int i = 3; i <= n; i += 3)
            table[i] = true;

        for (int i = 5; i <= n; i += 5)
            table[i] = true;

        for (int i = 7; i <= n; i += 7)
            table[i] = true;

        int result = 0;
        for (int i = 1; i <= n; i++)
        {
            if (table[i])
                result += i;
        }

        return result;
    }
};

int main()
{
    vector<int> ns = {
        7,  // 21
        10, // 40
        9,  // 30
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.sumOfMultiples(ns[group]) << endl;

    return 0;
}
