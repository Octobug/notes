#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    int mySqrt(int x)
    {
        if (x < 1)
        {
            return 0;
        }

        if (x < 4)
        {
            return 1;
        }

        int left = 0;
        int right = x;
        int mid;

        int max_mid = 1;
        for (int i = 1; i <= 15; i++)
        {
            max_mid *= 2;
        }

        max_mid *= 1.414213562373;

        while (left <= right)
        {
            mid = left + ((right - left) / 2);

            int overflow = 0;
            int square = -1;
            if (mid <= max_mid)
            {
                square = mid * mid;
                overflow = (square / mid) != mid;
            }
            else
            {
                overflow = 1;
            }

            if (square == x)
            {
                return mid;
            }
            else if (square < x && !overflow)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return right;
    }
};

int main()
{
    Solution s;

    int x;

    cout << "Please input x: ";
    cin >> x;

    int result = s.mySqrt(x);

    cout << result << endl;
}
