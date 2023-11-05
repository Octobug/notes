#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution
{
public:
    int maximumNumberOfStringPairs(vector<string> &words)
    {
        unordered_set<string> uset;

        for (int i = 0; i < words.size(); i++)
            uset.insert(words[i]);

        int result = 0;

        for (int i = 0; i < words.size(); i++)
        {
            if (words[i][0] == words[i][1])
                continue;
            reverse(words[i].begin(), words[i].end());
            if (uset.find(words[i]) != uset.end())
                result++;
        }

        return result / 2;
    }
};

int main()
{
    vector<vector<string>> words = {
        {"cd", "ac", "dc", "ca", "zz"},                               // 2
        {"ab", "ba", "cc"},                                           // 1
        {"aa", "ab"},                                                 // 0
        {"ff", "tx", "qr", "zw", "wr", "jr", "zt", "jk", "sq", "xx"}, // 0
    };

    int group;
    cout << "Please enter group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maximumNumberOfStringPairs(words[group]) << endl;

    return 0;
}
