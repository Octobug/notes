#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution
{
public:
    int evalRPN(vector<string> &tokens)
    {
        stack<int> stk;
        for (int i = 0; i < tokens.size(); i++)
        {
            string token = tokens[i];
            char op = token[0];
            if (token.size() == 1 && (op == '+' || op == '-' || op == '*' || op == '/'))
            {
                int a = stk.top();
                stk.pop();
                int b = stk.top();
                stk.pop();

                if (op == '+')
                {
                    stk.push(a + b);
                }
                else if (op == '-')
                {
                    stk.push(b - a);
                }
                else if (op == '*')
                {
                    stk.push(a * b);
                }
                else
                {
                    stk.push(b / a);
                }
            }
            else
            {
                stk.push(stoi(token));
            }
        }

        return stk.top();
    }
};

int main()
{
    vector<vector<string>> groups = {
        {"2", "1", "+", "3", "*"},
        {"4", "13", "5", "/", "+"},
        {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"},
    };

    int group;

    cout << "Please input group: ";
    cin >> group;

    Solution s;
    cout << s.evalRPN(groups[group - 1]) << endl;

    return 0;
}
