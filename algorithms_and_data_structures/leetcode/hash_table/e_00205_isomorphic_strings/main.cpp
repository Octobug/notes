#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool isIsomorphic(string s, string t)
    {
        int table1[128];
        int table2[128];
        int len = s.size();

        for (int i = 0; i < 128; i++)
        {
            table1[i] = INT_MIN;
            table2[i] = INT_MIN;
        }

        for (int i = 0; i < len; i++)
        {
            if (table1[s[i] - char(0)] == INT_MIN)
                table1[s[i] - char(0)] = t[i];
            else if (table1[s[i] - char(0)] != t[i])
                return false;

            if (table2[t[i] - char(0)] == INT_MIN)
                table2[t[i] - char(0)] = s[i];
            else if (table2[t[i] - char(0)] != s[i])
                return false;
        }

        return true;
    }
};

int main()
{
    vector<string> ss = {
        "egg",   // true
        "foo",   // false
        "paper", // true
        "badc",  // false
    };
    vector<string> tt = {
        "add",
        "bar",
        "title",
        "baba",
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.isIsomorphic(ss[group], tt[group]) << endl;

    return 0;
}
