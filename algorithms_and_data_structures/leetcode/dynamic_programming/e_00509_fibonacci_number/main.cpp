#include <iostream>

using namespace std;

class SolutionDP
{
public:
    int fib(int n)
    {
        if (n <= 1)
            return n;

        int dp[2];
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= n; i++)
        {
            int sum = dp[0] + dp[1];
            dp[0] = dp[1];
            dp[1] = sum;
        }
        return dp[1];
    }
};

class Solution
{
public:
    int fib(int n)
    {
        if (n == 0)
            return 0;

        int a = 0, b = 1;
        while (--n)
        {
            swap(a, b);
            b += a;
        }

        return b;
    }
};

int main()
{
    int n;
    cout << "Please input n: ";
    cin >> n;

    Solution s;
    cout << s.fib(n) << endl;

    return 0;
}
