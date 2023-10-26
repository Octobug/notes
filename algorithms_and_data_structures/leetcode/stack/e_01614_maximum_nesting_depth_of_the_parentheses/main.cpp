#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxDepth(string s)
    {
        int result = 0;
        int count = 0;

        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
            {
                count++;
                result = max(result, count);
            }
            else if (s[i] == ')')
                count--;
        }

        return result;
    }
};

int main()
{
    vector<string> ss = {
        "(1+(2*3)+((8)/4))+1", // 3
        "(1)+((2))+(((3)))",   // 3
    };

    int group;
    cout << "Please enter group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maxDepth(ss[group]) << endl;

    return 0;
}
