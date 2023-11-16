#include <iostream>
#include <vector>
#include "array.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    int result = 0;
    vector<string> words;
    vector<char> letters;
    vector<int> score;
    vector<int> available;
    vector<int> wordScores;

    void backtrack(int begin, int currScore)
    {
        result = max(result, currScore);
        for (int i = begin; i < words.size(); i++)
        {
            if (wordScores[i] == 0)
                continue;

            bool wordValid = true;
            for (int j = 0; j < words[i].size(); j++)
            {
                int letterIndex = words[i][j] - 'a';
                if (available[letterIndex] == 0)
                    wordValid = false;

                available[letterIndex]--;
            }

            if (wordValid)
                backtrack(i + 1, currScore + wordScores[i]);

            for (int j = 0; j < words[i].size(); j++)
                available[words[i][j] - 'a']++;
        }
    }

    int maxScoreWords(vector<string> &ws, vector<char> &ls, vector<int> &ss)
    {
        words = ws;
        letters = ls;
        score = ss;

        available = vector<int>(26, 0);
        wordScores = vector<int>(words.size(), 0);

        for (int i = 0; i < letters.size(); i++)
            available[letters[i] - 'a']++;

        for (int i = 0; i < words.size(); i++)
        {
            for (int j = 0; j < words[i].size(); j++)
            {
                if (available[words[i][j] - 'a'] == 0)
                {
                    wordScores[i] = 0;
                    break;
                }
                wordScores[i] += score[words[i][j] - 'a'];
            }
        }

        backtrack(0, 0);
        return result;
    }
};

int main()
{
    vector<vector<string>> words = {
        {"dog", "cat", "dad", "good"}, // 23
        {"xxxz", "ax", "bx", "cx"},    // 27
        {"leetcode"},                  // 0
    };
    vector<vector<char>> letters = {
        {'a', 'a', 'c', 'd', 'd', 'd', 'g', 'o', 'o'},
        {'z', 'a', 'b', 'c', 'x', 'x', 'x'},
        {'l', 'e', 't', 'c', 'o', 'd'},
    };
    vector<vector<int>> scores = {
        {1, 0, 9, 5, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0},
        {4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         5, 0, 10},
        {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0,
         0, 0, 0},
    };

    int group = getGroup();
    Solution s;

    cout << s.maxScoreWords(words[group], letters[group], scores[group])
         << endl;

    return 0;
}
