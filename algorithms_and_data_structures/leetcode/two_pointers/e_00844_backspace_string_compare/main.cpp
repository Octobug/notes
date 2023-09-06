#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution1
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
                back_count--;
                s[r_index] = '-';
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
                back_count--;
                t[r_index] = '-';
            }
            r_index--;
        }

        int s_index = 0, t_index = 0;
        while (s_index < s.size() || t_index < t.size())
        {
            while (s_index < s.size() && s[s_index] == '-')
                s_index++;

            while (t_index < t.size() && t[t_index] == '-')
                t_index++;

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

class Solution
{
public:
    bool backspaceCompare(string s, string t)
    {
        int lens = s.size(), lent = t.size();
        int is = lens - 1, it = lent - 1;
        int scount = 0, tcount = 0;

        while (is >= 0 && it >= 0)
        {
            if (s[is] != '#' && t[it] != '#')
            {
                if (scount == 0 && tcount == 0)
                {
                    if (s[is] != t[it])
                        return false;

                    is--;
                    it--;
                }
                else
                {
                    if (scount > 0)
                    {
                        scount--;
                        is--;
                    }
                    if (tcount > 0)
                    {
                        tcount--;
                        it--;
                    }
                }
            }
            else
            {
                if (s[is] == '#')
                {
                    scount++;
                    is--;
                }
                if (t[it] == '#')
                {
                    tcount++;
                    it--;
                }
            }
        }

        if (is == it)
            return true;

        int i, icount;
        string *sp;
        if (is > it)
        {
            i = is;
            icount = scount;
            sp = &s;
        }
        else
        {
            i = it;
            icount = tcount;
            sp = &t;
        }

        while (i >= 0)
        {
            if ((*sp)[i] == '#')
                icount++;
            else if (icount > 0)
                icount--;
            else
                return false;

            i--;
        }

        return true;
    }
};

int main()
{
    string s1 = "ab#c", t1 = "ad#c";           // 1
    string s2 = "ab##", t2 = "c#d#";           // 1
    string s3 = "a#c", t3 = "b";               // 0
    string s4 = "abcd####f", t4 = "fcaaf####"; // 1
    string s5 = "ab#cde#f", t5 = "acdf";       // 1
    string s6 = "aaa###a", t6 = "aaaa###a";    // 0

    vector groups_s = {s1, s2, s3, s4, s5, s6};
    vector groups_t = {t1, t2, t3, t4, t5, t6};
    int group;

    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.backspaceCompare(groups_s[group], groups_t[group]) << endl;
}
