#include <iostream>
#include <vector>

using namespace std;

class SolutionFunc
{
public:
    int bitCount(int num)
    {
        int count = 0;
        while (num)
        {
            if (num % 2)
                count++;
            num /= 2;
        }
        return count;
    }

    int sumIndicesWithKSetBits(vector<int> &nums, int k)
    {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
            if (bitCount(i) == k)
                sum += nums[i];

        return sum;
    }
};

class Solution
{
public:
    int sumIndicesWithKSetBits(vector<int> &nums, int k)
    {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            int bitCount = 0;
            int num = i;
            while (num)
            {
                if (num % 2)
                    bitCount++;
                num /= 2;
            }

            if (bitCount == k)
                sum += nums[i];
        }

        return sum;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {5, 10, 1, 5, 2}, // 13
        {4, 3, 2, 1},     // 1
    };
    vector<int> ks = {1, 2};
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.sumIndicesWithKSetBits(nums[group], ks[group]) << endl;

    return 0;
}
