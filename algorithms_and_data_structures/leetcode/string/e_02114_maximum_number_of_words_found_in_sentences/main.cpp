#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    int mostWordsFound(vector<string> &sentences)
    {
        int max = 0;
        for (int i = 0; i < sentences.size(); i++)
        {
            int count = 1;
            for (int j = 0; j < sentences[i].size(); j++)
            {
                if (sentences[i][j] == ' ')
                {
                    count++;
                }
            }
            if (count > max)
            {
                max = count;
            }
        }
        return max;
    }
};

int main()
{
    vector<string> sen1 = {
        "alice and bob love leetcode",
        "i think so too",
        "this is great thanks very much"};
    vector<string> sen2 = {
        "please wait",
        "continue to fight",
        "continue to win"};
    vector<vector<string>> groups = {sen1, sen2};

    int group;
    cout << "Please input group: ";
    cin >> group;

    Solution s;

    int result = s.mostWordsFound(groups[group - 1]);
    cout << result << endl;

    return 0;
}
