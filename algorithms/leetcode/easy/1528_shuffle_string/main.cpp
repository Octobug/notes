#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    string restoreString(string s, vector<int> &indices)
    {
        string s1(s.length(), '0');
        for (int i = 0; i < s.length(); i++)
        {
            s1[indices[i]] = s[i];
        }
        return s1;
    }
};

int main()
{
    Solution s;

    string str = "codeleet";
    vector<int> idx = {4, 5, 6, 7, 0, 2, 1, 3};
    string res = s.restoreString(str, idx);
    cout << res << endl;

    str = "abc";
    idx = {0, 1, 2};
    res = s.restoreString(str, idx);
    cout << res << endl;

    str = "aiohn";
    idx = {3, 1, 4, 2, 0};
    res = s.restoreString(str, idx);
    cout << res << endl;

    str = "aaiougrt";
    idx = {4, 0, 2, 6, 7, 3, 1, 5};
    res = s.restoreString(str, idx);
    cout << res << endl;

    str = "art";
    idx = {1, 0, 2};
    res = s.restoreString(str, idx);
    cout << res << endl;

    return 0;
}
