#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    string replaceDigits(string s)
    {
        for (int i = 0, j = 1; i < s.size(); i += 2, j += 2)
            s[j] = s[i] + s[j] - '0';

        return s;
    }
};

int main()
{
    vector<string> ss = {
        "a1c1e1",    // "abcdef"
        "a1b2c3d4e", // "abbdcfdhe"
    };

    int group;
    cout << "Please enter group; ";
    cin >> group;
    group--;

    Solution s;
    cout << s.replaceDigits(ss[group]) << endl;

    return 0;
}
