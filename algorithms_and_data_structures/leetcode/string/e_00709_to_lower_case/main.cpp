#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    string toLowerCase(string s)
    {
        int offset = 'a' - 'A';
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] >= 'A' && s[i] <= 'Z')
                s[i] += offset;
        }

        return s;
    }
};

int main()
{
    vector<string> ss = {
        "Hello",
        "here",
        "LOVELY",
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.toLowerCase(ss[group]) << endl;

    return 0;
}
