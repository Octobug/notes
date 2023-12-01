#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int minimumOneBitOperations(int n)
    {
        int result;
        int i = 0;
        for (result = 0; n > 0; n &= n - 1)
            result = -(result + (n ^ (n - 1)));

        return abs(result);
    }
};

int main()
{
    int n;
    cout << "Please enter n: ";
    cin >> n;

    Solution s;
    cout << s.minimumOneBitOperations(n) << endl;
}
