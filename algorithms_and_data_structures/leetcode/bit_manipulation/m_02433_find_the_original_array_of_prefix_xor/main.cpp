#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> findArray(vector<int> &pref)
    {
        vector<int> result = pref;
        int last = result[0], curr;

        for (int i = 1; i < result.size(); i++)
        {
            curr = result[i];
            result[i] = last ^ curr;
            last = curr;
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> perfs = {
        {5, 2, 0, 3, 1}, // [5,7,2,3,2]
        {13},            // [13]
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<int> result = s.findArray(perfs[group]);
    output(result);

    return 0;
}
