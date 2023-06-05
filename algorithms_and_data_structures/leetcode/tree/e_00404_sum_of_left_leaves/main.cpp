#include <iostream>
#include <queue>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
    bool isLeaf(TreeNode *node)
    {
        return !node->left && !node->right;
    }

public:
    int sumOfLeftLeaves(TreeNode *root)
    {
        int sum = 0;
        if (root == nullptr)
            return sum;

        queue<TreeNode *> que;
        que.push(root);

        while (!que.empty())
        {
            TreeNode *node = que.front();
            que.pop();

            if (node->left)
            {
                if (isLeaf(node->left))
                {
                    sum += node->left->val;
                }
                else
                {
                    que.push(node->left);
                }
            }

            if (node->right)
            {
                if (!isLeaf(node->right))
                {
                    que.push(node->right);
                }
            }
        }

        return sum;
    }
};

class SolutionRecursive
{
    int getSum(TreeNode *node, bool isLeft)
    {
        int sum = 0;
        if (!node->left && !node->right)
        {
            if (isLeft)
                return node->val;
            else
                return 0;
        }

        if (node->left)
        {
            sum += getSum(node->left, true);
        }

        if (node->right)
        {
            sum += getSum(node->right, false);
        }

        return sum;
    }

public:
    int sumOfLeftLeaves(TreeNode *root)
    {
        return getSum(root, false);
    }
};

int main()
{
    vector<vector<int>> groups = {
        {3, 9, 20, INT_MIN, INT_MIN, 15, 7},
        {1},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(groups[group]);

    Solution s;
    cout << s.sumOfLeftLeaves(root) << endl;

    return 0;
}
