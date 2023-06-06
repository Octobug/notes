#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
    TreeNode *construct(vector<int> &nums, int begin, int end)
    {
        if (begin >= end)
            return nullptr;

        int maxIdx = begin;
        for (int i = begin + 1; i < end; i++)
        {
            if (nums[i] > nums[maxIdx])
                maxIdx = i;
        }

        TreeNode *root = new TreeNode(nums[maxIdx]);
        root->left = construct(nums, begin, maxIdx);
        root->right = construct(nums, maxIdx + 1, end);

        return root;
    }

public:
    TreeNode *constructMaximumBinaryTree(vector<int> &nums)
    {
        return construct(nums, 0, nums.size());
    }
};

int main()
{
    vector<vector<int>> groups = {
        {3, 2, 1, 6, 0, 5},
        {3, 2, 1},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    TreeNode *root = s.constructMaximumBinaryTree(groups[group]);
    outputLevelOrder(root);

    return 0;
}
