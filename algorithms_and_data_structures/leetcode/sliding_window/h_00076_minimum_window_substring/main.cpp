#include <iostream>
#include <string>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    string minWindow(string s, string t)
    {
        vector<int> t_store(52, 0);
        vector<int> s_store(52, 0);
        int t_count = t.size();

        for (int i = 0; i < t.size(); i++)
        {
            int s_idx = this->c_index(t[i]);
            t_store[s_idx]++;
        }

        int min_len = s.size() + 1;
        int min_left = 0;
        int left = 0;

        for (int right = 0; right < s.size(); right++)
        {
            if (t_count != 0)
            {
                int s_idx = this->c_index(s[right]);
                if (t_store[s_idx])
                {
                    s_store[s_idx]++;
                    if (s_store[s_idx] <= t_store[s_idx])
                    {
                        t_count--;
                    }
                }
                if (t_count == 0)
                {
                    int cur_len = right - left + 1;
                    if (cur_len < min_len)
                    {
                        min_len = cur_len;
                        min_left = left;
                    }
                }
            }

            if (t_count == 0)
            {
                int s_idx = this->c_index(s[left]);
                if (t_store[s_idx])
                {
                    if (s_store[s_idx] == t_store[s_idx])
                    {
                        t_count++;
                    }
                    s_store[s_idx]--;
                    left++;
                }

                while (left <= right)
                {
                    s_idx = this->c_index(s[left]);
                    if (t_store[s_idx])
                    {
                        if (s_store[s_idx] <= t_store[s_idx])
                        {
                            break;
                        }
                        else
                        {
                            s_store[s_idx]--;
                        }
                    }
                    left++;
                }

                s_idx = this->c_index(s[right]);
                t_count++;
                s_store[s_idx]--;
                right--;
            }
        }

        if (min_len > s.size())
        {
            return "";
        }
        return s.substr(min_left, min_len);
    };

private:
    int c_index(char c)
    {
        if (c > 'Z')
        {
            return c - 'a';
        }
        else
        {
            return c - 'A' + 26;
        }
    }
};

int main()
{
    string s1 = "ADOBECODEBANC";
    string t1 = "ABC";

    string s2 = "a";
    string t2 = "a";

    string s3 = "a";
    string t3 = "aa";

    string s4 = "ab";
    string t4 = "a";

    string s5 = "ab";
    string t5 = "b";

    string s6 = "cabefgecdaecf";
    string t6 = "cae";

    string s7 = "aaflslflsldkalskaaa";
    string t7 = "aaa";

    vector<string> s_groups = {s1, s2, s3, s4, s5, s6, s7};
    vector<string> t_groups = {t1, t2, t3, t4, t5, t6, t7};

    int group;
    cout << "Please input group: ";
    cin >> group;

    Solution s;
    cout << s.minWindow(s_groups[group - 1], t_groups[group - 1]) << endl;

    return 0;
}
