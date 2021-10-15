#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    int minPartitions(string n)
    {
        int max = 0;
        for (string::iterator it = n.begin(); it != n.end(); ++it)
        {

            int num = *it - '0';
            if (num > max)
            {
                max = num;
            }
            if (max >= 9)
            {
                break;
            }
        }
        return max;
    }
};

int main()
{
    Solution s;
    string n = "27346209830709182346";
    int result = s.minPartitions(n);
    cout << result << endl;
}
