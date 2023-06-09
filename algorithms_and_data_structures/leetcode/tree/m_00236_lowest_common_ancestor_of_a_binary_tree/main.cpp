#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
    TreeNode *pnode;
    TreeNode *qnode;
    TreeNode *result = nullptr;

public:
    bool postFind(TreeNode *node)
    {
        if (result != nullptr)
            return true;

        bool leftFound = false;
        bool rightFound = false;

        if (node->left)
            leftFound = postFind(node->left);

        if (node->right)
            rightFound = postFind(node->right);

        if (result != nullptr)
            return true;

        if (leftFound && rightFound)
        {
            result = node;
            return true;
        }

        if (node->val == pnode->val || node->val == qnode->val)
        {
            if (leftFound || rightFound)
                result = node;

            return true;
        }

        if (leftFound || rightFound)
        {
            return true;
        }

        return false;
    }

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        pnode = p;
        qnode = q;
        postFind(root);
        return result;
    }
};

int main()
{
    vector<vector<vector<int>>> groups = {
        {{3, 5, 1, 6, 2, 0, 8, INT_MIN, INT_MIN, 7, 4}, {5, 1}},
        {{3, 5, 1, 6, 2, 0, 8, INT_MIN, INT_MIN, 7, 4}, {5, 4}},
        {{1, 2}, {1, 2}},
    };

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
