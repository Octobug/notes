#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    bool uniqueOccurrences(vector<int> &arr)
    {
        int table[2001] = {0};

        for (int i = 0; i < arr.size(); i++)
            table[arr[i] + 1000]++;

        bool count[1001] = {false};
        int num;
        for (int i = 0; i < 2001; i++)
        {
            num = table[i];
            if (num == 0)
                continue;
            if (count[num])
                return false;
            count[num] = true;
        }
        return true;
    }
};

int main()
{
    vector<vector<int>> arrs = {
        {1, 2, 2, 1, 1, 3},                 // 1
        {1, 2},                             // 0
        {-3, 0, 1, -3, 1, 1, 1, -3, 10, 0}, // 1
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.uniqueOccurrences(arrs[group]) << endl;

    return 0;
}
