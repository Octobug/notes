#include <iostream>
#include <unordered_set>

using namespace std;

class Solution
{
public:
    bool isHappy(int n)
    {
        unordered_set<int> set;
        while (n != 1)
        {
            int sum = 0, last;
            while (n)
            {
                last = n % 10;
                sum += last * last;
                n /= 10;
            }
            if (set.count(sum))
            {
                return false;
            }
            set.insert(sum);
            n = sum;
        }
        return true;
    }
};

int main()
{
    int n;
    cout << "Please input n: ";
    cin >> n;

    Solution s;
    cout << s.isHappy(n) << endl;

    return 0;
}
