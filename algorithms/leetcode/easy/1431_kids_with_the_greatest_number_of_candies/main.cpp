#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    vector<bool> kidsWithCandies(vector<int> &candies, int extraCandies)
    {
        int maxCandy = 0;
        // get the max number of candy
        for (int i = 0; i < candies.size(); i++)
        {
            if (candies[i] > maxCandy)
            {
                maxCandy = candies[i];
                if (maxCandy == 100)
                {
                    break;
                }
            }
        }

        // everyone has candies more than the max after given extra
        if (maxCandy < extraCandies)
        {
            vector<bool> ans(candies.size(), true);
            return ans;
        }

        // compare to the max
        vector<bool> ans(candies.size());
        maxCandy -= extraCandies;
        for (int i = 0; i < candies.size(); i++)
        {
            if (candies[i] >= maxCandy)
            {
                ans[i] = true;
            }
        }
        return ans;
    }
};

void output(vector<bool> &arr)
{
    cout << '[';
    cout << boolalpha;
    for (int i = 0; i < arr.size(); ++i)
    {
        cout << arr[i];
        if (i != arr.size() - 1)
        {
            cout << ',';
        }
    }
    cout << ']' << endl;
}

int main()
{
    Solution s;
    vector<int> in1 = {2, 3, 5, 1, 3};
    int ec1 = 3;
    vector<int> in2 = {4, 2, 1, 1, 2};
    int ec2 = 1;
    vector<int> in3 = {12, 1, 12};
    int ec3 = 10;
    vector<bool> res1 = s.kidsWithCandies(in1, ec1);
    vector<bool> res2 = s.kidsWithCandies(in2, ec2);
    vector<bool> res3 = s.kidsWithCandies(in3, ec3);
    output(res1);
    output(res2);
    output(res3);
}
