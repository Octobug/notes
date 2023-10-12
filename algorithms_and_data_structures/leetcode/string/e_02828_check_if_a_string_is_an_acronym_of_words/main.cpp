#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool isAcronym(vector<string> &words, string s)
    {
        if (words.size() != s.size())
            return false;

        for (int i = 0; i < s.size(); i++)
        {
            if (words[i][0] != s[i])
                return false;
        }

        return true;
    }
};

int main()
{
    vector<vector<string>> words = {
        {"alice", "bob", "charlie"},                   // 1
        {"an", "apple"},                               // 0
        {"never", "gonna", "give", "up", "on", "you"}, // 1
    };
    vector<string> ss = {
        "abc",
        "a",
        "ngguoy",
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.isAcronym(words[group], ss[group]) << endl;

    return 0;
}
