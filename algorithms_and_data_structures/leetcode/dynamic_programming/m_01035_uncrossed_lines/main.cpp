#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2)
    {
        int len1 = nums1.size();
        int len2 = nums2.size();

        int dp[len1 + 1][len2 + 1];

        for (int i = 0; i <= len1; i++)
            dp[i][0] = 0;

        for (int i = 0; i <= len2; i++)
            dp[0][i] = 0;

        for (int i = 1; i <= len1; i++)
        {
            for (int j = 1; j <= len2; j++)
            {
                if (nums1[i - 1] == nums2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        return dp[len1][len2];
    }
};

int main()
{
    vector<vector<int>> nums1 = {
        {1, 4, 2},          // 2
        {2, 5, 1, 2, 5},    // 3
        {1, 3, 7, 1, 7, 5}, // 2
    };

    vector<vector<int>> nums2 = {
        {1, 2, 4},
        {10, 5, 2, 1, 5, 2},
        {1, 9, 2, 5, 1},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.maxUncrossedLines(nums1[group], nums2[group]) << endl;

    return 0;
}
