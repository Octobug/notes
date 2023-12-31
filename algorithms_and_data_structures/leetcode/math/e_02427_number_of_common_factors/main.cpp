#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int commonFactors(int a, int b)
    {
        int result = 1;
        int limit = min(a, b);

        for (int i = 2; i <= limit; i++)
        {
            if (a % i == 0 && b % i == 0)
                result++;
        }
        return result;
    }
};

int main()
{
    vector<int> as = {
        12, // 4
        25, // 2
    };

    vector<int> bs = {6, 30};

    int g = getGroup();
    Solution s;
    cout << s.commonFactors(as[g], bs[g]) << endl;

    return 0;
}
