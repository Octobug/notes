#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
    vector<vector<int>> result;
    vector<int> comb;
    int sum = 0;

    void backtrack(int k, int n, int start)
    {
        if (comb.size() == k)
        {
            if (sum == n)
                result.push_back(comb);

            return;
        }

        int leftCount;
        for (int i = start;; i++)
        {
            leftCount = k - comb.size();
            if (i > ((n - sum) / leftCount) + 1)
                break;
            if (i > (9 - leftCount + 1))
                break;

            comb.push_back(i);
            sum += i;
            backtrack(k, n, i + 1);
            comb.pop_back();
            sum -= i;
        }
    }

public:
    vector<vector<int>> combinationSum3(int k, int n)
    {
        backtrack(k, n, 1);
        return result;
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {3, 7},
        {3, 9},
        {4, 1},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<int>> result = s.combinationSum3(inputs[group][0], inputs[group][1]);
    output2d(result);

    return 0;
}
