#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    string replaceSpace(string s)
    {
        string result;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ' ')
            {
                result += "%20";
            }
            else
            {
                result += s[i];
            }
        }
        return result;
    }
};

int main()
{
    vector<string> groups = {
        "We are happy.",
    };

    int group;

    cout << "Please input group: ";
    cin >> group;

    Solution s;
    cout << s.replaceSpace(groups[group - 1]) << endl;

    return 0;
}
