#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> processQueries(vector<int> &queries, int m)
    {
        int len = queries.size();
        vector<int> result(len);
        vector<int> p(m);

        for (int i = 0; i < m; i++)
            p[i] = i + 1;

        for (int i = 0; i < len; i++)
        {
            auto it = find(p.begin(), p.end(), queries[i]);

            int index = it - p.begin();
            result[i] = index;

            for (int j = index; j > 0; j--)
                p[j] = p[j - 1];
            p[0] = queries[i];
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> queries = {
        {3, 1, 2, 1},    // [2,1,2,1]
        {4, 1, 2, 2},    // [3,1,2,0]
        {7, 5, 5, 8, 3}, // [6,5,0,7,5]
    };
    vector<int> ms = {
        5,
        4,
        8,
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<int> result = s.processQueries(queries[group], ms[group]);
    output(result);

    return 0;
}
