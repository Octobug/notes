#include <iostream>

using namespace std;

class Solution
{
public:
    int smallestEvenMultiple(int n)
    {
        if (n % 2 == 0)
        {
            return n;
        }
        else
        {
            return n * 2;
        }
    }
};

int main()
{
    int n;
    cout << "Please input n: ";
    cin >> n;

    Solution s;
    cout << s.smallestEvenMultiple(n) << endl;
    return 0;
}
