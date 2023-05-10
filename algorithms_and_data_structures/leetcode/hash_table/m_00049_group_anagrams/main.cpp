#include <iostream>
#include <unordered_map>
#include <vector>
#include <array.h>

using namespace std;

class Solution
{
public:
    string uniqueKey(string word)
    {
        int table[26] = {0};
        for (int i = 0; i < word.size(); i++)
        {
            table[word[i] - 'a']++;
        }

        int wordIdx = 0;
        while (wordIdx < word.size())
        {
            for (int tableIdx = 0; tableIdx < 26; tableIdx++)
            {
                int count = table[tableIdx];
                while (count--)
                {
                    word[wordIdx++] = 'a' + tableIdx;
                }
            }
        }
        return word;
    }

    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        vector<vector<string>> result;
        unordered_map<string, int> store;

        for (int i = 0; i < strs.size(); i++)
        {
            string key = this->uniqueKey(strs[i]);

            if (store.count(key))
            {
                result[store[key]].push_back(strs[i]);
            }
            else
            {
                vector<string> group = {strs[i]};
                result.push_back(group);
                store[key] = result.size() - 1;
            }
        }

        return result;
    }
};

int main()
{
    vector<string> strs1 = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<string> strs2 = {""};
    vector<string> strs3 = {"a"};

    vector<vector<string>> groups = {strs1, strs2, strs3};
    int group;
    cout << "Please input group: ";
    cin >> group;

    Solution s;
    vector<vector<string>> result = s.groupAnagrams(groups[group - 1]);
    output2d(result);

    return 0;
}
