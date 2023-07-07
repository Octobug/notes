#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int profit = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            profit += max(prices[i] - prices[i - 1], 0);
        }
        return profit;
    }
};

class SolutionComplex
{
public:
    int maxProfit(vector<int> &prices)
    {
        int profit = 0;
        int buy = prices[0];

        for (int i = 0; i < prices.size() - 1; i++)
        {
            if (buy > prices[i])
            {
                buy = prices[i];
            }
            else
            {
                if (prices[i] > prices[i + 1])
                {
                    profit += prices[i] - buy;
                    buy = prices[i + 1];
                }
                else if (i == prices.size() - 2)
                {
                    profit += (prices[i + 1] - buy);
                }
            }
        }

        return profit;
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {7, 1, 5, 3, 6, 4},
        {1, 2, 3, 4, 5},
        {7, 6, 4, 3, 1},
        {1, 2},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maxProfit(inputs[group]) << endl;

    return 0;
}
