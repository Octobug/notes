#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "array.h"

using namespace std;

class SolutionGraph
{
public:
    unordered_map<string, vector<string *>> graph;

    int bfs(string &beginWord, string &endWord)
    {
        queue<string> que;
        que.push(beginWord);
        que.push("");
        int result = 0;

        while (!que.empty())
        {
            string cur = que.front();
            que.pop();

            if (cur.size() == 0)
            {
                result++;
                if (!que.empty())
                    que.push("");
                continue;
            }

            if (cur == endWord)
                return result + 1;

            for (auto it = graph[cur].begin(); it != graph[cur].end(); ++it)
                que.push(**it);

            graph.erase(cur);
        }

        return 0;
    }

    void add2Graph(vector<string> &wordList, string &first, string &second)
    {
        int diff = 0;
        for (int k = 0; k < first.size(); k++)
        {
            if (first[k] != second[k])
                diff++;

            if (diff > 1)
                return;
        }

        graph[first].push_back(&second);
        graph[second].push_back(&first);
    }

    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        // build graph
        for (int i = 0; i < wordList.size(); i++)
        {
            add2Graph(wordList, beginWord, wordList[i]);
            for (int j = i + 1; j < wordList.size(); j++)
                add2Graph(wordList, wordList[i], wordList[j]);
        }

        if (graph.find(endWord) == graph.end())
            return 0;

        return bfs(beginWord, endWord);
    }
};

class Solution
{
public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());

        if (wordSet.find(endWord) == wordSet.end())
            return 0;

        unordered_map<string, int> visitMap;
        queue<string> que;

        que.push(beginWord);
        visitMap.insert(pair<string, int>(beginWord, 1));

        while (!que.empty())
        {
            string word = que.front();
            que.pop();
            int path = visitMap[word];
            for (int i = 0; i < word.size(); i++)
            {
                string newWord = word;
                for (int j = 0; j < 26; j++)
                {
                    newWord[i] = j + 'a';
                    if (newWord == endWord)
                        return path + 1;

                    if (wordSet.find(newWord) != wordSet.end() &&
                        visitMap.find(newWord) == visitMap.end())
                    {
                        visitMap.insert(pair<string, int>(newWord, path + 1));
                        que.push(newWord);
                    }
                }
            }
        }
        return 0;
    }
};

int main()
{
    vector<vector<string>> wls = {
        {"hot", "dot", "dog", "lot", "log", "cog"}, // 5
        {"hot", "dot", "dog", "lot", "log"},        // 0
    };
    vector<string> bws = {"hit", "hit"};
    vector<string> ews = {"cog", "cog"};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.ladderLength(bws[group], ews[group], wls[group]) << endl;

    return 0;
}
