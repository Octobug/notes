#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    TreeNode *targetOrigin;
    TreeNode *targetCopy;

    void traverse(TreeNode *o, TreeNode *c)
    {
        if (o == targetOrigin)
            targetCopy = c;

        if (o->left)
            traverse(o->left, c->left);

        if (o->right)
            traverse(o->right, c->right);
    }

    TreeNode *getTargetCopy(TreeNode *original, TreeNode *cloned, TreeNode *target)
    {
        targetOrigin = target;
        traverse(original, cloned);
        return targetCopy;
    }
};

TreeNode *getTargetNode(TreeNode *root, int target)
{
    if (root->val == target)
        return root;

    if (root->left)
    {
        TreeNode *left = getTargetNode(root->left, target);
        if (left && left->val == target)
            return left;
    }

    if (root->right)
    {
        TreeNode *right = getTargetNode(root->right, target);
        if (right && right->val == target)
            return right;
    }

    return nullptr;
}

int main()
{
    vector<vector<int>> trees = {
        {7, 4, 3, INT_MIN, INT_MIN, 6, 19},
        {7},
    };
    vector<int> targets = {3, 7};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *original = array2treeLevelOrder(trees[group]);
    TreeNode *cloned = array2treeLevelOrder(trees[group]);
    TreeNode *target = getTargetNode(original, targets[group]);

    Solution s;
    TreeNode *targetCopy = s.getTargetCopy(original, cloned, target);
    cout << targetCopy->val << endl;

    return 0;
}
