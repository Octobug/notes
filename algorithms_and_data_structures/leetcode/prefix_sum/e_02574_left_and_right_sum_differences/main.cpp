#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> leftRigthDifference(vector<int> &nums)
    {
        vector<int> answer(nums.size(), 0);

        int leftSum = 0;
        int rightSum = 0;

        for (int i = 0; i < nums.size() - 1; i++)
        {
            leftSum += nums[i];
            answer[i + 1] = leftSum;
        }

        for (int i = nums.size() - 1; i > 0; i--)
        {
            rightSum += nums[i];
            if (answer[i - 1] >= rightSum)
            {
                answer[i - 1] = answer[i - 1] - rightSum;
            }
            else
            {
                answer[i - 1] = rightSum - answer[i - 1];
            }
        }

        return answer;
    }
};

int main()
{
    vector<int> nums1 = {10, 4, 8, 3};
    vector<int> nums2 = {1};

    vector<vector<int>> groups = {nums1, nums2};
    int group;

    cout << "Please input group: ";
    cin >> group;

    Solution s;
    vector<int> result = s.leftRigthDifference(groups[group - 1]);
    output(result);

    return 0;
}
