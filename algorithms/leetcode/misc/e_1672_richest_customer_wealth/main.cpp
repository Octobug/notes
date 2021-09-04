#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    int maximumWealth(vector<vector<int>> &accounts)
    {
        int maxWealth = 0;
        int sum = 0;
        for (int i = 0; i < accounts.size(); i++)
        {
            sum = 0;
            for (int j = 0; j < accounts[i].size(); j++)
            {
                sum += accounts[i][j];
            }
            if (sum > maxWealth)
            {
                maxWealth = sum;
            }
        }
        return maxWealth;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> in1 = {{1, 2, 3}, {3, 2, 1}};
    vector<vector<int>> in2 = {{1, 5}, {7, 3}, {3, 5}};
    int res1 = s.maximumWealth(in1);
    int res2 = s.maximumWealth(in2);
    cout << res1 << endl;
    cout << res2 << endl;
}
