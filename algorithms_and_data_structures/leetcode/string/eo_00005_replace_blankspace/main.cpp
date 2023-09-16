#include <iostream>
#include <vector>

using namespace std;

class SolutionStr
{
public:
    string replaceSpace(string s)
    {
        string result;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ' ')
                result += "%20";
            else
                result += s[i];
        }
        return result;
    }
};

class Solution
{
public:
    string replaceSpace(string s)
    {
        int spaceCount = 0;
        int originLen = s.size();

        for (int i = 0; i < originLen; i++)
            if (s[i] == ' ')
                spaceCount++;

        s.resize(originLen + spaceCount * 2);
        int newLen = s.size();
        for (int i = originLen - 1, j = newLen - 1; i >= 0; i--, j--)
        {
            if (s[i] == ' ')
            {
                s[j] = '0';
                s[j - 1] = '2';
                s[j - 2] = '%';
                j -= 2;
            }
            else
                s[j] = s[i];
        }

        return s;
    }
};

int main()
{
    vector<string> ss = {
        "We are happy.",
    };

    int group;

    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.replaceSpace(ss[group]) << endl;

    return 0;
}
