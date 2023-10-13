#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    string reverseWords(string s)
    {
        int begin = 0;

        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ' ')
            {
                reverse(s.begin() + begin, s.begin() + i);
                begin = i + 1;
            }
        }
        reverse(s.begin() + begin, s.end());

        return s;
    }
};

int main()
{
    vector<string> ss = {
        "Let's take LeetCode contest", // "s'teL ekat edoCteeL tsetnoc"
        "God Ding",                    // "doG gniD"
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.reverseWords(ss[group]) << endl;

    return 0;
}
