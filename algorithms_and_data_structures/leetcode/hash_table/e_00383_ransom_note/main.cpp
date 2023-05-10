#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool canConstruct(string ransomNote, string magazine)
    {
        vector<int> table(26, 0);

        for (int i = 0; i < magazine.size(); i++)
        {
            table[magazine[i] - 'a']++;
        }

        for (int i = 0; i < ransomNote.size(); i++)
        {
            table[ransomNote[i] - 'a']--;
            if (table[ransomNote[i] - 'a'] < 0)
            {
                return false;
            }
        }

        return true;
    }
};

int main()
{
    string rsn1 = "a", mgz1 = "b";
    string rsn2 = "aa", mgz2 = "ab";
    string rsn3 = "aa", mgz3 = "aab";

    vector<string> rsngroups = {rsn1, rsn2, rsn3};
    vector<string> mgzgroups = {mgz1, mgz2, mgz3};

    int group;
    cout << "Please input group: ";
    cin >> group;

    Solution s;
    cout << s.canConstruct(rsngroups[group - 1], mgzgroups[group - 1]) << endl;

    return 0;
}
