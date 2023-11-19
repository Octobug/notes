#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include "array.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    int minFlips(vector<vector<int>> mat)
    {
        queue<vector<pair<int, int>>> que;
        int m = mat.size(), n = mat[0].size();
        int dirs[5][2] = {
            {0, 0},
            {-1, 0},
            {0, -1},
            {1, 0},
            {0, 1},
        };

        int result = 0;
        int numOf1 = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (mat[i][j] == 1)
                    numOf1++;
            }
        }

        if (numOf1 == 0)
            return result;

        que.push({});
        int limit = m * n;
        while (result <= limit)
        {
            int queSize = que.size();
            result++;
            for (int r = 0; r < queSize; r++)
            {
                vector<pair<int, int>> comb = que.front();
                que.pop();
                pair<int, int> last = {0, -1};
                if (comb.size() > 0)
                    last = comb[comb.size() - 1];

                int start = last.first * n + last.second + 1;
                int i = start / n, j = start % n;
                while (i < m && j < n)
                {
                    vector<vector<int>> newmat = mat;
                    int leftToFlip = numOf1;
                    vector<pair<int, int>> newcomb = comb;
                    newcomb.push_back({i, j});

                    for (int c = 0; c < newcomb.size(); c++)
                    {
                        auto [x, y] = newcomb[c];
                        for (int di = 0; di < 5; di++)
                        {
                            int nx = x + dirs[di][0];
                            int ny = y + dirs[di][1];

                            if (nx < 0 || nx >= m || ny < 0 || ny >= n)
                                continue;

                            newmat[nx][ny] ^= 1;

                            if (newmat[nx][ny] == 1)
                                leftToFlip++;
                            else
                                leftToFlip--;
                        }

                        if (leftToFlip == 0)
                            return result;
                    }

                    que.push(newcomb);

                    start++;
                    i = start / n, j = start % n;
                }
            }
        }
        return -1;
    }
};

int main()
{
    vector<vector<vector<int>>> mats = {
        {
            {0, 0},
            {0, 1},
        }, // 3
        {
            {0},
        }, // 0
        {
            {1, 0, 0},
            {1, 0, 0},
        }, // -1
        {
            {1, 1, 1},
            {1, 0, 1},
            {0, 0, 0},
        }, // 6
    };
    int group = getGroup();
    Solution s;
    cout << s.minFlips(mats[group]) << endl;

    return 0;
}
