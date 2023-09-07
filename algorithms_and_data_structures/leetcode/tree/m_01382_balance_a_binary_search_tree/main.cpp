#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    vector<int> nums;

    TreeNode *build(vector<int> &nums, int begin, int end)
    {
        if (begin > end)
            return nullptr;

        int mid = (begin + end) / 2;
        TreeNode *node = new TreeNode(nums[mid]);

        node->left = build(nums, begin, mid - 1);
        node->right = build(nums, mid + 1, end);

        return node;
    }

    void inorderTraverse(TreeNode *node)
    {
        if (node->left)
            inorderTraverse(node->left);

        nums.push_back(node->val);

        if (node->right)
            inorderTraverse(node->right);
    }

    TreeNode *balanceBST(TreeNode *root)
    {
        inorderTraverse(root);
        return build(nums, 0, nums.size() - 1);
    }
};

int main()
{
    vector<vector<int>> roots = {
        {1, INT_MIN, 2, INT_MIN, 3, INT_MIN, 4,
         INT_MIN, INT_MIN}, // 2,1,3,null,null,null,4
        {2, 1, 3},          // 2,1,3
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(roots[group]);

    Solution s;
    TreeNode *result = s.balanceBST(root);
    outputLevelOrder(result);

    return 0;
}
