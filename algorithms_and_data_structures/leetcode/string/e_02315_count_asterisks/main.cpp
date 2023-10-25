#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int countAsterisks(string s)
    {
        int result = 0;
        bool isInPair = false;

        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '|')
                isInPair = !isInPair;

            if (s[i] == '*' && !isInPair)
                result++;
        }

        return result;
    }
};

int main()
{
    vector<string> ss = {
        "l|*e*et|c**o|*de|",          // 2
        "iamprogrammer",              // 0
        "yo|uar|e**|b|e***au|tifu|l", // 5
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.countAsterisks(ss[group]) << endl;

    return 0;
}
