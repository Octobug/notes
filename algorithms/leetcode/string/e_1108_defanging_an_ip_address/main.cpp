#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    string defangIPaddr(string address)
    {
        string result;
        for (string::iterator it = address.begin(); it != address.end(); ++it)
        {
            if (*it == '.')
            {
                result += "[.]";
            }
            else
            {
                result += *it;
            }
        }
        return result;
    }
};

int main()
{
    Solution s;
    string input = "1.1.1.1";
    string result = s.defangIPaddr(input);
    cout << result << endl;
}
