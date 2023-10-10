#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    string sortSentence(string s)
    {
        vector<int> wordEndIndex(10, 0);

        int slen = s.size();
        int count = 0;
        for (int i = 0; i < slen; i++)
        {
            if (isalpha(s[i]))
            {
                count++;
            }
            else
            {
                if (isdigit(s[i]))
                    wordEndIndex[s[i] - '0'] = count;

                count = 0;
            }
        }

        wordEndIndex[0] = -2;
        for (int i = 1; i < 10; i++)
        {
            if (wordEndIndex[i] == 0)
            {
                wordEndIndex.resize(i);
                break;
            }

            wordEndIndex[i] += wordEndIndex[i - 1] + 1;
        }

        string result = s;
        int wordIndex = s[slen - 1] - '0';

        for (int j = s.size() - 1; j >= 0; j--)
        {
            if (isdigit(s[j]))
            {
                wordIndex = s[j] - '0';
            }
            else
            {
                int letterIndex = wordEndIndex[wordIndex];
                result[letterIndex + 1] = ' ';
                while (j >= 0 && isalpha(s[j]))
                    result[letterIndex--] = s[j--];
            }
        }

        result.resize(wordEndIndex[wordEndIndex.size() - 1] + 1);

        return result;
    }
};

int main()
{
    vector<string> ss = {
        "is2 sentence4 This1 a3", // "This is a sentence"
        "Myself2 Me1 I4 and3",    // "Me Myself and I"
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.sortSentence(ss[group]) << endl;

    return 0;
}
