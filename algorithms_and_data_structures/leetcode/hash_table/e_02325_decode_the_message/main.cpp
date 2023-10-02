#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    string decodeMessage(string key, string message)
    {
        char table[123] = {0};
        char c = 'a';

        table[' '] = ' ';
        for (int i = 0; i < key.size(); i++)
        {
            if (table[key[i]] == 0)
                table[key[i]] = c++;
        }

        for (int i = 0; i < message.size(); i++)
            message[i] = table[message[i]];

        return message;
    }
};

int main()
{
    vector<string> keys = {
        "the quick brown fox jumps over the lazy dog", // "this is a secret"
        "eljuxhpwnyrdgtqkviszcfmabo",                  // "the five boxing wizards jump quickly"
    };
    vector<string> msgs = {
        "vkbs bs t suepuv",
        "zwx hnfx lqantp mnoeius ycgk vcnjrdb",
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.decodeMessage(keys[group], msgs[group]) << endl;

    return 0;
}
