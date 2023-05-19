#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class SolutionDumb
{
public:
    bool isValid(string s)
    {
        stack<char> stk;

        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[')
            {
                stk.push(s[i]);
            }
            else
            {
                if (stk.empty())
                {
                    return false;
                }
                else if (s[i] == ')' && stk.top() == '(')
                {
                    stk.pop();
                }
                else if (s[i] == '}' && stk.top() == '{')
                {
                    stk.pop();
                }
                else if (s[i] == ']' && stk.top() == '[')
                {
                    stk.pop();
                }
                else
                {
                    return false;
                }
            }
        }

        if (stk.empty())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> stk;

        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
            {
                stk.push(')');
            }
            else if (s[i] == '[')
            {
                stk.push(']');
            }
            else if (s[i] == '{')
            {
                stk.push('}');
            }
            else
            {
                if (stk.empty())
                {
                    return false;
                }
                else if (s[i] == stk.top())
                {
                    stk.pop();
                }
                else
                {
                    return false;
                }
            }
        }

        if (stk.empty())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

int main()
{
    vector<string> groups = {
        "()",
        "()[]{}",
        "(]",
        "[",
    };
    int group;
    cout << "Please input group: ";
    cin >> group;

    Solution s;
    cout << s.isValid(groups[group - 1]) << endl;
    return 0;
}
