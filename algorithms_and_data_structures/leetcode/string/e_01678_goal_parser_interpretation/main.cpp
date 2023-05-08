#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    string interpret(string command)
    {
        int idx = 0;
        string result = "";
        while (idx < command.size())
        {
            if (command[idx] == 'G')
            {
                result += 'G';
                idx++;
            }
            else if (command[idx] == '(' && command[idx + 1] == ')')
            {
                result += 'o';
                idx += 2;
            }
            else
            {
                result += "al";
                idx += 4;
            }
        }
        return result;
    }
};

int main()
{
    string c1 = "G()(al)";
    string c2 = "G()()()()(al)";
    string c3 = "(al)G(al)()()G";

    vector<string> groups = {c1, c2, c3};
    int group;

    cout << "Please input group: ";
    cin >> group;

    Solution s;
    string result = s.interpret(groups[group - 1]);
    cout << result << endl;

    return 0;
}
