#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    bool backspaceCompare(string s, string t)
    {
        int back_count = 0;
        int r_index = s.size() - 1;

        while (r_index >= 0)
        {
            if (s[r_index] == '#')
            {
                back_count++;
                s[r_index] = '-';
            }
            else if (back_count > 0)
            {
                s[r_index] = '-';
                back_count--;
            }
            r_index--;
        }

        back_count = 0;
        r_index = t.size() - 1;
        while (r_index >= 0)
        {
            if (t[r_index] == '#')
            {
                back_count++;
                t[r_index] = '-';
            }
            else if (back_count > 0)
            {
                t[r_index] = '-';
                back_count--;
            }
            r_index--;
        }

        int t_index = 0, s_index = 0;

        while (s_index < s.size() || t_index < t.size())
        {
            while (s_index < s.size() && s[s_index] == '-')
            {
                s_index++;
            }
            while (t_index < t.size() && t[t_index] == '-')
            {
                t_index++;
            }
            if (s[s_index] != t[t_index])
            {
                return false;
            }
            else
            {
                s_index++;
                t_index++;
            }
        }

        return true;
    }
};

int main()
{
    string s1 = "ab#c", t1 = "ad#c";
    string s2 = "ab##", t2 = "c#d#";
    string s3 = "a#c", t3 = "b";
    string s4 = "abcd####f", t4 = "fcaaf####";
    string s5 = "ab#cde#f", t5 = "acdf";
    string s6 = "aaa###a", t6 = "aaaa###a";

    vector groups_s = {s1, s2, s3, s4, s5, s6};
    vector groups_t = {t1, t2, t3, t4, t5, t6};
    int group;

    cout << "Please input group: ";
    cin >> group;

    group--;

    Solution s;
    bool equal = s.backspaceCompare(groups_s[group], groups_t[group]);

    cout << equal << endl;
}
