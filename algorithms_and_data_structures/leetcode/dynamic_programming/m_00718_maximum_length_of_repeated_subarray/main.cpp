#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution1D
{
public:
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        int len1 = nums1.size();
        int len2 = nums2.size();

        int dp[len2 + 1];

        for (int i = 0; i <= len2; i++)
            dp[i] = 0;

        int result = 0;

        for (int i = 1; i <= len1; i++)
        {
            for (int j = len2; j >= 1; j--)
            {
                if (nums1[i - 1] == nums2[j - 1])
                    dp[j] = dp[j - 1] + 1;
                else
                    dp[j] = 0;

                result = max(result, dp[j]);
            }
        }

        return result;
    }
};

class Solution
{
public:
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        int len1 = nums1.size();
        int len2 = nums2.size();

        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
        int result = 0;

        for (int i = 1; i <= len1; i++)
        {
            for (int j = 1; j <= len2; j++)
            {
                if (nums1[i - 1] == nums2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;

                result = max(result, dp[i][j]);
            }
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> nums1 = {
        {1, 2, 3, 2, 1}, // 3
        {0, 0, 0, 0, 0}, // 5
        {3, 2, 1, 4, 7}, // 3
    };
    vector<vector<int>> nums2 = {
        {3, 2, 1, 4, 7},
        {0, 0, 0, 0, 0},
        {1, 2, 3, 2, 1},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.findLength(nums1[group], nums2[group]) << endl;

    return 0;
}
