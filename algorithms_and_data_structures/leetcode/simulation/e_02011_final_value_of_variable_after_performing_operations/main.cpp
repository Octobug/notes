#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int finalValueAfterOperations(vector<string> &operations)
    {
        int x = 0;
        for (int i = 0; i < operations.size(); i++)
        {
            if (operations[i] == "++X" || operations[i] == "X++")
            {
                x++;
            }
            else
            {
                x--;
            }
        }
        return x;
    }
};

int main()
{
    vector<string> ops1 = {"--X", "X++", "X++"};
    vector<string> ops2 = {"++X", "++X", "X++"};
    vector<string> ops3 = {"X++", "++X", "--X", "X--"};
    vector<vector<string>> groups = {ops1, ops2, ops3};

    int group;
    cout << "Please input group: ";
    cin >> group;

    Solution s;
    int res = s.finalValueAfterOperations(groups[group - 1]);
    cout << res << endl;

    return 0;
}
