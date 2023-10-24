#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution
{
public:
    string removeOuterParentheses(string s)
    {
        string result(s.size(), ' ');
        stack<int> stk;
        int cursor = 0;

        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
            {
                stk.push(i);
            }
            else
            {
                int begin = stk.top();
                stk.pop();
                if (stk.empty())
                {
                    for (int j = begin + 1; j < i; j++)
                        result[cursor++] = s[j];
                }
            }
        }

        result.resize(cursor);
        return result;
    }
};

int main()
{
    vector<string> ss = {
        "(()())(())",         // "()()()"
        "(()())(())(()(()))", // "()()()()(())"
        "()()",               // ""
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.removeOuterParentheses(ss[group]) << endl;

    return 0;
}
