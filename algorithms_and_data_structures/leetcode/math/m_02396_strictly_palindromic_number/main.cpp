#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    bool isStrictlyPalindromic(int n)
    {
        for (int i = 2; i <= n - 2; i++)
        {
            vector<int> cvtAndRvsed = this->convertBaseReversed(n, i);

            int begin = 0, end = cvtAndRvsed.size() - 1;
            while (begin < end)
            {
                if (cvtAndRvsed[begin] != cvtAndRvsed[end])
                {
                    return false;
                }
                begin++;
                end--;
            }
        }
        return true;
    }

    vector<int> convertBaseReversed(int n, int b)
    {
        vector<int> digits;
        while (n > 0)
        {
            digits.push_back(n % b);
            n /= b;
        }

        return digits;
    }
};

int main()
{
    int n;
    cout << "Please input n: ";
    cin >> n;

    Solution s;
    bool result = s.isStrictlyPalindromic(n);

    cout << result << endl;
    return 0;
}
