#include <iostream>
#include <vector>

using namespace std;

class SolutionVec
{
public:
    int candy(vector<int> &ratings)
    {
        vector<int> candyVec(ratings.size(), 1);
        for (int i = 1; i < ratings.size(); i++)
        {
            if (ratings[i] > ratings[i - 1])
                candyVec[i] = candyVec[i - 1] + 1;
        }

        for (int i = ratings.size() - 2; i >= 0; i--)
        {
            if (ratings[i] > ratings[i + 1])
                candyVec[i] = max(candyVec[i], candyVec[i + 1] + 1);
        }

        int result = 0;
        for (int i = 0; i < candyVec.size(); i++)
            result += candyVec[i];

        return result;
    }
};

class Solution
{
public:
    int candy(vector<int> &ratings)
    {
        if (ratings.size() == 1)
            return 1;

        int total = 1;
        int lastMaxIndex = 0;
        int lastMaxCandy = 1;

        for (int i = 1; i < ratings.size(); i++)
        {
            if (ratings[i] > ratings[i - 1])
            {
                if (i - lastMaxIndex > 1)
                    lastMaxCandy = 2;
                else
                    lastMaxCandy++;

                lastMaxIndex = i;
                total += lastMaxCandy;
            }
            else if (ratings[i] < ratings[i - 1])
            {
                int distance = i - lastMaxIndex;
                if (lastMaxCandy > distance)
                    total += distance;
                else
                    total += distance + 1;
            }
            else
            {
                lastMaxIndex = i;
                lastMaxCandy = 1;
                total++;
            }
        }

        return total;
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {1, 0, 2},             // 5
        {1, 2, 2},             // 4
        {1, 3, 2, 2, 1},       // 7
        {1, 2, 3, 1, 0},       // 9
        {0, 1, 2, 5, 3, 2, 7}, // 15
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.candy(inputs[group]) << endl;

    return 0;
}
