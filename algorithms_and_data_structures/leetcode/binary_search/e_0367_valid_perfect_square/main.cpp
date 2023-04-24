#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    bool isPerfectSquare(int num)
    {
        int left = 1;
        int right = num;
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

            bool overflow = false;
            int square = -1;
            if (mid <= max_mid)
            {
                square = mid * mid;
                overflow = (square / mid) != mid;
            }
            else
            {
                overflow = true;
            }

            if (square == num)
            {
                return true;
            }
            else if (square < num && !overflow)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return false;
    }
};

int main()
{
    Solution s;

    int num;

    cout << "Please input num: ";
    cin >> num;

    bool result = s.isPerfectSquare(num);

    cout << result << endl;
}
