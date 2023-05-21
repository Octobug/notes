#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution
{
public:
    string simplifyPath(string path)
    {
        stack<string> stk;
        int left = 1, right = 1;
        string unit;

        while (left < path.size() && right < path.size())
        {
            while (path[left] == '/' && left < path.size())
            {
                left++;
            }
            right = left;
            while (path[right] != '/' && right < path.size())
            {
                right++;
            }
            unit = path.substr(left, right - left);

            if (unit == "/" || unit == "." || unit == "")
            {
                right++;
            }
            else if (unit == "..")
            {
                if (!stk.empty())
                {
                    stk.pop();
                }
            }
            else
            {
                stk.push(unit);
            }

            left = right;
        }

        if (stk.empty())
        {
            return "/";
        }

        int size = stk.size();
        string res = "";
        for (int i = 0; i < size; i++)
        {
            res = "/" + stk.top() + res;
            stk.pop();
        }
        return res;
    }
};

int main()
{
    vector<string> groups = {
        "/home/",
        "/../",
        "/home//foo/",
        "/a/./b/../../c/",
    };
    int group;
    cout << "Please input group: ";
    cin >> group;

    Solution s;
    cout << s.simplifyPath(groups[group - 1]) << endl;

    return 0;
}
