#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int numberOfMatches(int n)
    {
        int result = 0;

        while (n > 1)
        {
            if (n % 2 == 0)
            {
                n /= 2;
                result += n;
            }
            else
            {
                n = (n - 1) / 2;
                result += n;
                n += 1;
            }
        }

        return result;
    }
};

int main()
{
    int n;
    cout << "Please input n: ";
    cin >> n;

    Solution s;
    cout << s.numberOfMatches(n) << endl;

    return 0;
}
