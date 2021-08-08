#include <iostream>
#include <vector>
#include <string>

using namespace std;

void output(vector<int> &arr)
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

class Solution
{
public:
    vector<int> smallerNumbersThanCurrent(vector<int> &nums)
    {
        vector<int> count(101);
        vector<int> res(nums.size());

        for (int i = 0; i < nums.size(); i++)
        {
            count[nums[i]]++;
        }

        int tmp1 = 0;
        int tmp2 = count[0];
        count[0] = 0;
        int tmp3 = count[0];
        for (int i = 1; i < 101; i++)
        {
            if (count[i])
            {
                tmp1 = count[i];
                count[i] = tmp2 + tmp3;
                tmp2 = count[i];
                tmp3 = tmp1;
            }
        }

        for (int i = 0; i < nums.size(); i++)
        {
            res[i] = count[nums[i]];
        }

        return res;
    }
};

int main()
{
    Solution s;
    vector<int> in1 = {8, 1, 2, 2, 3};
    vector<int> in2 = {6, 5, 4, 8};
    vector<int> in3 = {7, 7, 7, 7};
    vector<int> in4 = {5, 0, 10, 0, 10, 6};
    vector<int> res1 = s.smallerNumbersThanCurrent(in1);
    vector<int> res2 = s.smallerNumbersThanCurrent(in2);
    vector<int> res3 = s.smallerNumbersThanCurrent(in3);
    vector<int> res4 = s.smallerNumbersThanCurrent(in4);
    output(res1);
    output(res2);
    output(res3);
    output(res4);
}
