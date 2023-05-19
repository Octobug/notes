#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class SolutionStack
{
public:
    string removeDuplicates(string s)
    {
        stack<char> stk;

        for (int i = 0; i < s.size(); i++)
        {
            if (stk.empty())
            {
                stk.push(s[i]);
            }
            else
            {
                if (stk.top() == s[i])
                {
                    stk.pop();
                }
                else
                {
                    stk.push(s[i]);
                }
            }
        }

        int newLeng = stk.size();
        for (int i = newLeng - 1; i >= 0; i--)
        {
            s[i] = stk.top();
            stk.pop();
        }

        s.resize(newLeng);
        return s;
    }
};

class Solution
{
public:
    string removeDuplicates(string s)
    {
        int len = s.size();
        if (len == 1)
        {
            return s;
        }

        int left = 0, right = 1;
        while (right < len)
        {
            if (s[left] == s[right])
            {
                s[left] = ' ';
                s[right++] = ' ';

                while (s[left] == ' ')
                {

                    if (left == 0)
                    {
                        left = right;
                        right++;
                        break;
                    }
                    left--;
                }
            }
            else
            {
                left = right;
                right++;
            }
        }

        left = 0, right = 0;
        while (right < len)
        {
            if (s[right] != ' ')
            {
                s[left++] = s[right];
            }
            right++;
        }

        s.resize(left);

        return s;
    }
};

int main()
{
    vector<string> groups = {
        "abbaca",
        "azxxzy",
        "ibfjcaffccadidiaidchakchchcahabhibdcejkdkfbaeeaecdjhajbkfebebfea",
        "aaaaaaaa",
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    Solution s;
    cout << s.removeDuplicates(groups[group - 1]) << endl;

    return 0;
}
