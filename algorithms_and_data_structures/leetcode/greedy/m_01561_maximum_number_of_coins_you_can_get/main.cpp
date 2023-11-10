#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int maxCoins(vector<int> &piles)
    {
        sort(piles.rbegin(), piles.rend());

        int limit = piles.size() / 3 * 2;
        int result = 0;

        for (int i = 1; i < limit; i += 2)
            result += piles[i];

        return result;
    }
};

int main()
{
    vector<vector<int>> piles = {
        {2, 4, 1, 2, 7, 8},          // 9
        {2, 4, 5},                   // 4
        {9, 8, 7, 6, 5, 1, 2, 3, 4}, // 18
    };

    int group = getGroup();
    Solution s;
    cout << s.maxCoins(piles[group]) << endl;

    return 0;
}
