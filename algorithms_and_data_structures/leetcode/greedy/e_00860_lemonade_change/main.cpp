#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool lemonadeChange(vector<int> &bills)
    {
        int five = 0, ten = 0;
        for (int i = 0; i < bills.size(); i++)
        {
            if (bills[i] == 5)
                five++;
            else if (bills[i] == 10)
            {
                ten++;
                if (five < 1)
                    return false;
                five--;
            }
            else
            {
                if (ten >= 1 && five >= 1)
                {
                    five--;
                    ten--;
                }
                else if (five >= 3)
                    five -= 3;
                else
                    return false;
            }
        }
        return true;
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {5, 5, 5, 10, 20},
        {5, 5, 10, 10, 20},
        {5, 5, 5, 10, 5, 5, 10, 20, 20, 20},
        {5, 5, 5, 5, 20, 20, 5, 5, 20, 5},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.lemonadeChange(inputs[group]) << endl;

    return 0;
}
