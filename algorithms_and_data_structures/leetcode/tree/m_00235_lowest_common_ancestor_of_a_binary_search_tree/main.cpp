#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
    TreeNode *small;
    TreeNode *large;

public:
    TreeNode *find(TreeNode *node)
    {
        if (node->left && node->val > large->val)
            return find(node->left);
        else if (node->right && node->val < small->val)
            return find(node->right);
        else
            return node;
    }

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (p->val > q->val)
        {
            small = q;
            large = p;
        }
        else
        {
            small = p;
            large = q;
        }

        return find(root);
    }
};

class SolutionIteration
{

public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        TreeNode *small;
        TreeNode *large;

        if (p->val > q->val)
        {
            small = q;
            large = p;
        }
        else
        {
            small = p;
            large = q;
        }

        while (root)
        {
            if (root->val > large->val)
                root = root->left;
            else if (root->val < small->val)
                root = root->right;
            else
                return root;
        }

        return nullptr;
    }
};

int main()
{
    vector<vector<vector<int>>> groups = {
        {{6, 2, 8, 0, 4, 7, 9, INT_MIN, INT_MIN, 3, 5}, {2, 8}},
        {{6, 2, 8, 0, 4, 7, 9, INT_MIN, INT_MIN, 3, 5}, {2, 4}},
        {{2, 1}, {2, 1}},
        {{6, 2, 8, 0, 4, 7, 9, INT_MIN, INT_MIN, 3, 5}, {3, 5}}};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(groups[group][0]);
    TreeNode *p = new TreeNode(groups[group][1][0]);
    TreeNode *q = new TreeNode(groups[group][1][1]);

    Solution s;
    TreeNode *result = s.lowestCommonAncestor(root, p, q);
    cout << result->val << endl;

    return 0;
}
