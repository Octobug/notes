#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    int product = 1;
    int sum = 0;
    int tmp = 0;
    int subtractProductAndSum(int n)
    {
        product = 1;
        sum = 0;
        while (n)
        {
            tmp = n % 10;
            product *= tmp;
            sum += tmp;
            n /= 10;
        }

        return product - sum;
    }
};

int main()
{
    Solution s;

    int n = 234;
    int ans = s.subtractProductAndSum(n);
    cout << ans << endl;

    n = 4421;
    ans = s.subtractProductAndSum(n);
    cout << ans << endl;
}
