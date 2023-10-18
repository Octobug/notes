#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    string finalString(string s)
    {
        int cur = 0;

        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == 'i')
            {
                if (i + 1 < s.size())
                {
                    if (s[i + 1] == 'i')
                        i++;
                    else
                        reverse(s.begin(), s.begin() + cur);
                }
                else
                    reverse(s.begin(), s.begin() + cur);
            }
            else
            {
                s[cur++] = s[i];
            }
        }

        s.resize(cur);

        return s;
    }
};

int main()
{
    vector<string> ss = {
        "string",   // "rtsng"
        "poiinter", // "ponter"
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.finalString(ss[group]) << endl;

    return 0;
}
