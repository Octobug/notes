#include <iostream>
#include <vector>
#include "array.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    int earliestFullBloom(vector<int> &plantTime, vector<int> &growTime)
    {
        vector<int> seq(plantTime.size());
        for (int i = 0; i < plantTime.size(); i++)
            seq[i] = i;

        sort(seq.begin(), seq.end(),
             [&pt = plantTime, &gt = growTime](int a, int b) -> bool
             {
                 return gt[a] > gt[b];
             });

        int result = 0;
        int pTime = 0;
        for (int i = 0; i < plantTime.size(); i++)
        {
            pTime += plantTime[seq[i]];
            result = max(result, pTime + growTime[seq[i]]);
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> plantTimes = {
        {1, 4, 3},    // 9
        {1, 2, 3, 2}, // 9
        {1},          // 2
    };
    vector<vector<int>> growTimes = {
        {2, 3, 1},
        {2, 1, 2, 1},
        {1},
    };

    int group = getGroup();

    Solution s;
    cout << s.earliestFullBloom(plantTimes[group], growTimes[group]) << endl;

    return 0;
}
