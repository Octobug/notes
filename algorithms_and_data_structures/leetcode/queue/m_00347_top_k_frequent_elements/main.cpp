#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    class cmp
    {
    public:
        bool operator()(pair<int, int> &a, pair<int, int> &b)
        {
            return a.second > b.second;
        }
    };

    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++)
        {
            map[nums[i]]++;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> priQue;

        for (unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++)
        {
            priQue.push(*it);
            if (priQue.size() > k)
            {
                priQue.pop();
            }
        }

        vector<int> result(k);
        for (int i = 0; i < k; i++)
        {
            result[i] = priQue.top().first;
            priQue.pop();
        }
        return result;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {1, 1, 1, 2, 2, 3},
        {1},
    };
    int group, k;
    cout << "Please input group: ";
    cin >> group;
    cout << "Please input k: ";
    cin >> k;

    Solution s;
    vector<int> result = s.topKFrequent(groups[group - 1], k);
    output(result);
    return 0;
}
