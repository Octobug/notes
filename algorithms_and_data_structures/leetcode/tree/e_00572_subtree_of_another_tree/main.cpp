#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include "bintree.h"

using namespace std;

class SolutionSlow
{
public:
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        if (p == nullptr && q == nullptr)
            return true;

        queue<TreeNode *> que;
        que.push(p);
        que.push(q);

        while (!que.empty())
        {
            TreeNode *pnode = que.front();
            que.pop();

            TreeNode *qnode = que.front();
            que.pop();

            if (!pnode && !qnode)
            {
                continue;
            }
            else if (!pnode || !qnode || (pnode->val != qnode->val))
            {
                return false;
            }

            que.push(pnode->left);
            que.push(qnode->left);
            que.push(pnode->right);
            que.push(qnode->right);
        }

        return true;
    }

    bool isSubtree(TreeNode *root, TreeNode *subRoot)
    {
        stack<TreeNode *> stk;
        stk.push(root);

        while (!stk.empty())
        {
            TreeNode *node = stk.top();
            if (node != nullptr)
            {
                stk.pop();
                if (node->right)
                    stk.push(node->right);
                if (node->left)
                    stk.push(node->left);
                stk.push(node);
                stk.push(nullptr);
            }
            else
            {
                stk.pop();
                node = stk.top();
                stk.pop();
                if (isSameTree(node, subRoot))
                {
                    return true;
                }
            }
        }
        return false;
    }
};

class Solution
{
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        if (!p && !q)
            return true;
        if (!p || !q)
            return false;
        if (p->val != q->val)
            return false;

        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }

public:
    bool isSubtree(TreeNode *root, TreeNode *subRoot)
    {
        if (!root)
            return false;
        if (isSameTree(root, subRoot))
            return true;
        bool x = false, y = false;
        if (root->left)
            x = isSubtree(root->left, subRoot);
        if (root->right)
            y = isSubtree(root->right, subRoot);
        return x || y;
    }
};

int main()
{
    vector<vector<vector<int>>> groups = {
        {{3, 4, 5, 1, 2}, {4, 1, 2}},
        {{3, 4, 5, 1, 2, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 0}, {4, 1, 2}},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(groups[group][0]);
    TreeNode *subRoot = array2treeLevelOrder(groups[group][1]);

    Solution s;
    cout << s.isSubtree(root, subRoot) << endl;

    return 0;
}
