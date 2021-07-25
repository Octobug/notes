#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    int uppersOffset = (int)'A';
    int lowersOffset = (int)'a';
    int numJewelsInStones(string jewels, string stones)
    {
        vector<int> uppers(26);
        vector<int> lowers(26);
        int count = 0;

        // mark jewels
        for (int i = 0; i < jewels.length(); i++)
        {
            if (jewels[i] >= 'a')
            {
                lowers[jewels[i] - lowersOffset] = 1;
            }
            else
            {
                uppers[jewels[i] - uppersOffset] = 1;
            }
        }

        // count jewels
        for (int i = 0; i < stones.length(); i++)
        {
            if (stones[i] >= 'a')
            {
                if (lowers[stones[i] - lowersOffset])
                {
                    count++;
                }
            }
            else
            {
                if (uppers[stones[i] - uppersOffset])
                {
                    count++;
                }
            }
        }

        return count;
    }
};

int main()
{
    Solution s;
    string jewels1 = "aA", stones1 = "aAAbbbb";
    int result1 = s.numJewelsInStones(jewels1, stones1);
    cout << result1 << endl;

    string jewels2 = "z", stones2 = "ZZ";
    int result2 = s.numJewelsInStones(jewels2, stones2);
    cout << result2 << endl;
}
