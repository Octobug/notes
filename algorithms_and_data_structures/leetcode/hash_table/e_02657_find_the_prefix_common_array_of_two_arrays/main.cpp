#include <iostream>
#include <vector>
#include "array.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    vector<int> findThePrefixCommonArray(vector<int> &A, vector<int> &B)
    {
        int table[51] = {0};

        vector<int> result(A.size(), 0);
        int count = 0;
        for (int i = 0; i < A.size(); i++)
        {
            table[A[i]]++;
            if (table[A[i]] == 2)
                count++;

            table[B[i]]++;
            if (table[B[i]] == 2)
                count++;

            result[i] = count;
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> As = {
        {1, 3, 2, 4}, // [0,2,3,4]
        {2, 3, 1},    // [0,1,3]
        {1, 2, 3},    // [1,1,3]
        {1, 2, 3},    // [0,1,3]
    };
    vector<vector<int>> Bs = {
        {3, 1, 2, 4},
        {3, 1, 2},
        {1, 3, 2},
        {3, 1, 2},
    };

    int group = getGroup();
    Solution s;
    vector<int> result = s.findThePrefixCommonArray(As[group], Bs[group]);
    output(result);

    return 0;
}
