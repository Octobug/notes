#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int sumOfTheDigitsOfHarshadNumber(int x)
    {
        int sum = 0;
        int n = x;
        while (n > 0)
        {
            sum += n % 10;
            n /= 10;
        }

        if (x % sum == 0)
            return sum;

        return -1;
    }
};

int main()
{
    vector<int> xs = {
        18, // 9
        23, // -1
    };

    int g = getGroup();
    Solution s;
    cout << s.sumOfTheDigitsOfHarshadNumber(xs[g]) << endl;

    return 0;
}
