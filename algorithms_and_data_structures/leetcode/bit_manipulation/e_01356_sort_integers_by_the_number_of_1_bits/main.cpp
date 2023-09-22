#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    short table[10001] = {0};

    vector<int> sortByBits(vector<int> &arr)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            int num = arr[i];

            if (table[arr[i]] != 0)
                table[arr[i]] = 0;

            while (num > 0)
            {
                table[arr[i]] += num % 2;
                num /= 2;
                // num &= (num - 1); // 清除最低位的1
                // table[arr[i]]++;
            }
        }

        sort(arr.begin(), arr.end(),
             [&table = table](int a, int b) -> bool
             {
                 if (table[a] != table[b])
                     return table[a] < table[b];
                 else
                     return a < b;
             });
        return arr;
    }
};

int main()
{
    vector<vector<int>> arrs = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8},                   // [0,1,2,4,8,3,5,6,7]
        {1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1}, // [1,2,4,8,16,32,64,128,256,512,1024]
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<int> result = s.sortByBits(arrs[group]);
    output(result);

    return 0;
}
