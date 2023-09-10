#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int balancedStringSplit(string s)
    {
        int result = 0;
        int flag = 0;

        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == 'R')
                flag++;
            else if (s[i] == 'L')
                flag--;

            if (flag == 0)
                result++;
        }

        return result;
    }
};

int main()
{
    vector<string> ss = {
        "RLRRLLRLRL", // 4
        "RLRRRLLRLL", // 2
        "LLLLRRRR",   // 1
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.balancedStringSplit(ss[group]) << endl;

    return 0;
}
