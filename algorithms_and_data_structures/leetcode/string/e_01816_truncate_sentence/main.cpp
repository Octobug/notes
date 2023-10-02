#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    string truncateSentence(string s, int k)
    {
        int i = 0;
        for (; i < s.size(); i++)
        {
            if (s[i] == ' ')
                k--;
            if (k == 0)
            {
                s.resize(i);
                break;
            }
        }

        return s;
    }
};

int main()
{
    vector<string> ss = {
        "Hello how are you Contestant",         // "Hello how are you"
        "What is the solution to this problem", // "What is the solution"
        "chopper is not a tanuki",              // "chopper is not a tanuki"
    };
    vector<int> ks = {4, 4, 5};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.truncateSentence(ss[group], ks[group]) << endl;

    return 0;
}
