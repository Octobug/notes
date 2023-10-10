#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool checkIfPangram(string sentence)
    {
        bool alphabet[26] = {false};

        for (int i = 0; i < sentence.size(); i++)
            alphabet[sentence[i] - 'a'] = true;

        for (int i = 0; i < 26; i++)
            if (!alphabet[i])
                return false;

        return true;
    }
};

int main()
{
    vector<string> sentences = {
        "thequickbrownfoxjumpsoverthelazydog", // 1
        "leetcode",                            // 0
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.checkIfPangram(sentences[group]) << endl;

    return 0;
}
