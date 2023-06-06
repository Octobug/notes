#include <iostream>
#include <queue>
#include <vector>
#include "bintree.h"

using namespace std;

class SolutionRecursive
{
public:
    TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2)
    {
        if (root1 == nullptr)
            return root2;
        else if (root2 == nullptr)
            return root1;

        root1->val += root2->val;

        root1->left = mergeTrees(root1->left, root2->left);
        root1->right = mergeTrees(root1->right, root2->right);
        return root1;
    }
};

class Solution
{
public:
    TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2)
    {
        if (t1 == nullptr)
            return t2;
        if (t2 == nullptr)
            return t1;

        queue<TreeNode *> que;
        que.push(t1);
        que.push(t2);

        while (!que.empty())
        {
            TreeNode *node1 = que.front();
            que.pop();
            TreeNode *node2 = que.front();
            que.pop();

            node1->val += node2->val;

            if (node1->left != nullptr && node2->left != nullptr)
            {
                que.push(node1->left);
                que.push(node2->left);
            }
            if (node1->right != nullptr && node2->right != nullptr)
            {
                que.push(node1->right);
                que.push(node2->right);
            }

            if (node1->left == nullptr && node2->left != nullptr)
            {
                node1->left = node2->left;
            }
            if (node1->right == nullptr && node2->right != nullptr)
            {
                node1->right = node2->right;
            }
        }
        return t1;
    }
};

int main()
{
    vector<vector<vector<int>>> groups = {
        {{1, 3, 2, 5}, {2, 1, 3, INT_MIN, 4, INT_MIN, 7}},
        {{1}, {1, 2}},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root1 = array2treeLevelOrder(groups[group][0]);
    TreeNode *root2 = array2treeLevelOrder(groups[group][1]);

    Solution s;
    TreeNode *root = s.mergeTrees(root1, root2);
    outputLevelOrder(root);

    return 0;
}
