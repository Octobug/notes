#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution
{
public:
    int uniqueMorseRepresentations(vector<string> &words)
    {
        if (words.size() == 1)
            return 1;

        string morse[26] = {
            ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
            ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
            "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
        unordered_set<string> coded;

        for (int i = 0; i < words.size(); i++)
        {
            string trans(words[i].size() * 4, '-');
            int cursor = 0;

            for (int j = 0; j < words[i].size(); j++)
            {
                string *str = &morse[words[i][j] - 'a'];
                for (int k = 0; k < str->size(); k++)
                    trans[cursor++] = str->at(k);
            }

            trans.resize(cursor);
            coded.insert(trans);
        }

        return coded.size();
    }
};

int main()
{
    vector<vector<string>> words = {
        {"gin", "zen", "gig", "msg"}, // 2
        {"a"},                        // 1
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.uniqueMorseRepresentations(words[group]) << endl;

    return 0;
}
