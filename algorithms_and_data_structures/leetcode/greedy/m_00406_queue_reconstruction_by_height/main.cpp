#include <iostream>
#include <list>
#include <vector>
#include "array.h"

using namespace std;

class SolutionInsert
{
public:
    static bool cmp(const vector<int> &a, const vector<int> &b)
    {
        if (a[0] == b[0])
            return a[1] < b[1];
        return a[0] > b[0];
    }

    vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
    {
        sort(people.begin(), people.end(), cmp);
        vector<vector<int>> que;
        for (int i = 0; i < people.size(); i++)
        {
            int position = people[i][1];
            que.insert(que.begin() + position, people[i]);
        }
        return que;
    }
};

class SolutionLinked
{
public:
    static bool cmp(const vector<int> &a, const vector<int> &b)
    {
        if (a[0] == b[0])
            return a[1] < b[1];
        return a[0] > b[0];
    }

    vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
    {
        sort(people.begin(), people.end(), cmp);
        list<vector<int>> que;

        for (int i = 0; i < people.size(); i++)
        {
            int position = people[i][1];
            list<vector<int>>::iterator it = que.begin();
            while (position--)
                it++;
            que.insert(it, people[i]);
        }
        return vector<vector<int>>(que.begin(), que.end());
    }
};

class Solution
{

    static bool cmp(vector<int> a, vector<int> b)
    {
        if (a[0] == b[0])
            return a[1] > b[1];

        return a[0] < b[0];
    }

public:
    vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
    {
        sort(people.begin(), people.end(), cmp);
        vector<vector<int>> result(people.size(), {-1, 0});

        int index;
        int count;
        for (int i = 0; i < people.size(); i++)
        {
            index = 0;
            count = 0;
            while (count <= people[i][1])
            {
                if (result[index][0] == -1)
                    count++;
                index++;
            }
            result[index - 1] = people[i];
        }

        return result;
    }
};

int main()
{
    vector<vector<vector<int>>> inputs = {
        {{7, 0}, {4, 4}, {7, 1}, {5, 0}, {6, 1}, {5, 2}},
        {{6, 0}, {5, 0}, {4, 0}, {3, 2}, {2, 2}, {1, 4}},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<int>> result = s.reconstructQueue(inputs[group]);
    output2d(result);

    return 0;
}
