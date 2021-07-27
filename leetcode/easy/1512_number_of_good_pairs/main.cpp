#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution2
{
public:
    int result = 0;

    int nc2(int n)
    {
        return n * (n - 1) / 2;
    }

    int numIdenticalPairs(vector<int> &nums)
    {
        result = 0;
        vector<int> tmp(100, 0);
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] >= 100)
            {
                continue;
            }
            tmp[nums[i]]++;
        }
        for (int i = 0; i < tmp.size(); i++)
        {
            if (tmp[i] > 1)
            {
                result += nc2(tmp[i]);
            }
        }
        return result;
    }
};

class Solution1
{
public:
    int result = 0;
    int numIdenticalPairs(vector<int> &nums)
    {
        result = 0;
        for (int i = 0; i < nums.size() - 1; i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (nums[i] == nums[j])
                {
                    result++;
                }
            }
        }
        return result;
    }
};

int main()
{
    vector<int> in1 = {1, 2, 3, 1, 1, 3};
    vector<int> in2 = {1, 1, 1, 1};
    vector<int> in3 = {1, 2, 3};
    Solution1 s1;
    int res1 = s1.numIdenticalPairs(in1);
    cout << res1 << endl;
    res1 = s1.numIdenticalPairs(in2);
    cout << res1 << endl;
    res1 = s1.numIdenticalPairs(in3);
    cout << res1 << endl;

    Solution2 s2;
    int res2 = s2.numIdenticalPairs(in1);
    cout << res2 << endl;
    res2 = s2.numIdenticalPairs(in2);
    cout << res2 << endl;
    res2 = s2.numIdenticalPairs(in3);
    cout << res2 << endl;
    vector<int> in4 = {5, 5, 1, 77, 96, 96, 89, 80, 12, 23, 1, 6, 3, 66, 39, 88, 48, 38, 44, 32, 44, 36, 60, 87, 53, 77, 72, 49, 13, 39, 60, 60, 71, 68, 80, 75, 79, 38, 4, 14, 59, 75, 6, 91, 87, 95, 25, 55, 83, 18, 26, 59, 53, 100, 42, 96, 76, 22, 21, 4, 22, 46, 34, 39, 98, 82, 54, 73, 52, 33, 47, 73, 54, 23, 82, 98, 13, 51, 52, 1, 96, 69, 76};
    res2 = s2.numIdenticalPairs(in4);
    cout << res2 << endl;

    return 0;
}
