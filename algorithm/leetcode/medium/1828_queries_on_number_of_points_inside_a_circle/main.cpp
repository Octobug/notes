#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    vector<int> countPoints(vector<vector<int>> &points,
                            vector<vector<int>> &queries)
    {
        vector<int> result;
        int count;
        int tmpX;
        int tmpY;
        int tmpRR;
        for (int i = 0; i < queries.size(); i++)
        {
            count = 0;
            tmpRR = queries[i][2] * queries[i][2];
            for (int j = 0; j < points.size(); j++)
            {
                tmpX = queries[i][0] - points[j][0];
                tmpY = queries[i][1] - points[j][1];
                if ((tmpX * tmpX + tmpY * tmpY) <= tmpRR)
                {
                    count++;
                }
            }
            result.push_back(count);
        }
        return result;
    }
};

void output(vector<int> &arr)
{
    cout << '[';
    for (int i = 0; i < arr.size(); ++i)
    {
        cout << arr[i];
        if (i != arr.size() - 1)
        {
            cout << ',';
        }
    }
    cout << ']' << endl;
}

int main()
{
    Solution s;
    vector<vector<int>> points1 = {{1, 3}, {3, 3}, {5, 3}, {2, 2}};
    vector<vector<int>> queries1 = {{2, 3, 1}, {4, 3, 1}, {1, 1, 2}};
    vector<int> result1 = s.countPoints(points1, queries1);
    output(result1);

    vector<vector<int>> points2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    vector<vector<int>> queries2 = {{1, 2, 2}, {2, 2, 2}, {4, 3, 2}, {4, 3, 3}};
    vector<int> result2 = s.countPoints(points2, queries2);
    output(result2);
}
