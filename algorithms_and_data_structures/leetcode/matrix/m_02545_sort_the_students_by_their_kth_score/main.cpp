#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<vector<int>> sortTheStudents(vector<vector<int>> &score, int k)
    {
        sort(score.begin(), score.end(),
             [&k = k](vector<int> a, vector<int> b) -> bool
             {
                 return a[k] > b[k];
             });

        return score;
    }
};

int main()
{
    vector<vector<vector<int>>> scores = {
        {
            {10, 6, 9, 1},
            {7, 5, 11, 2},
            {4, 8, 3, 15},
        }, // [[7,5,11,2],[10,6,9,1],[4,8,3,15]]
        {
            {3, 4},
            {5, 6},
        }, // [[5,6],[3,4]]
    };
    vector<int> ks = {2, 0};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<int>> result = s.sortTheStudents(scores[group], ks[group]);
    output2d(result);

    return 0;
}
