#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class SolutionMax
{
public:
    vector<int> partitionLabels(string s)
    {
        int hash[26] = {0};

        for (int i = 0; i < s.size(); i++)
            hash[s[i] - 'a'] = i;

        vector<int> result;
        int left = 0;
        int right = 0;

        for (int i = 0; i < s.size(); i++)
        {
            right = max(right, hash[s[i] - 'a']);
            if (i == right)
            {
                result.push_back(right - left + 1);
                left = i + 1;
            }
        }
        return result;
    }
};

class Solution
{
    static bool cmp(vector<int> &a, vector<int> &b)
    {
        if (a[0] == -1)
            return false;

        if (b[0] == -1)
            return true;

        return a[0] < b[0];
    }

public:
    vector<int> partitionLabels(string s)
    {
        vector<vector<int>> account(26, {-1, -1});
        vector<int> result;

        for (int i = 0; i < s.size(); i++)
        {
            if (account[s[i] - 'a'][0] == -1)
                account[s[i] - 'a'][0] = i;
            account[s[i] - 'a'][1] = max(account[s[i] - 'a'][1], i);
        }

        sort(account.begin(), account.end(), cmp);

        int left = 0;
        int right = account[0][1];
        for (int i = 1; i < account.size() && account[i][0] != -1; i++)
        {
            if (account[i][0] < right)
            {
                right = max(right, account[i][1]);
            }
            else
            {
                result.push_back(right - left + 1);
                left = account[i][0];
                right = account[i][1];
            }
        }
        result.push_back(s.size() - left);

        return result;
    }
};

int main()
{
    vector<string> inputs = {
        "ababcbacadefegdehijhklij",
        "eccbbbbdec",
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<int> result = s.partitionLabels(inputs[group]);
    output(result);

    return 0;
}
