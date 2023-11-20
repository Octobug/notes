#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "input.h"

using namespace std;

class MyCalendarThree
{
public:
    map<int, int> pointCounts;

    MyCalendarThree()
    {
    }

    int book(int start, int end)
    {
        pointCounts[start]++;
        pointCounts[end]--;
        int result = 0;
        int alive = 0;
        for (auto i : pointCounts)
        {
            alive += i.second;
            result = max(result, alive);
        }
        return result;
    }
};

int main()
{
    vector<vector<vector<int>>> inputs = {
        {
            {10, 20}, // 1
            {50, 60}, // 1
            {10, 40}, // 2
            {5, 15},  // 3
            {5, 10},  // 3
            {25, 55}, // 3
        },
    };

    int group = getGroup();

    MyCalendarThree *cal = new MyCalendarThree();
    for (int i = 0; i < inputs[group].size(); i++)
        cout << cal->book(inputs[group][i][0], inputs[group][i][1]) << endl;

    return 0;
}
