#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int countDigits(int num)
    {
        int quotient = num;
        int count = 0;

        while (quotient > 0)
        {
            if (num % (quotient % 10) == 0)
                count++;

            quotient /= 10;
        }

        return count;
    }
};

int main()
{
    vector<int> nums = {
        7,    // 1
        121,  // 2
        1248, // 4
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.countDigits(nums[group]) << endl;

    return 0;
}
