#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int minOperations(int n)
    {
        if (n % 2 == 0)
            return n * n / 4;
        else
            return (n * n - 1) / 4;
    }
};

int main()
{
    // 3: 2
    // 6: 9
    // 31: 240

    int n;
    cout << "Please input n: ";
    cin >> n;

    Solution s;
    cout << s.minOperations(n) << endl;

    return 0;
}
