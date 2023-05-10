#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        if (s.size() != t.size())
        {
            return false;
        }

        vector<int> table(26, 0);

        for (int i = 0; i < s.size(); i++)
        {
            table[s[i] - 'a']++;
        }

        for (int i = 0; i < t.size(); i++)
        {
            table[t[i] - 'a']--;
            if (table[t[i] - 'a'] < 0)
            {
                return false;
            }
        }

        return true;
    }
};

int main()
{
    string s1 = "anagram", t1 = "nagaram";
    string s2 = "rat", t2 = "car";

    vector<string> sgroups = {s1, s2};
    vector<string> tgroups = {t1, t2};

    int group;
    cout << "Please input group: ";
    cin >> group;

    Solution s;
    cout << s.isAnagram(sgroups[group - 1], tgroups[group - 1]) << endl;

    return 0;
}
