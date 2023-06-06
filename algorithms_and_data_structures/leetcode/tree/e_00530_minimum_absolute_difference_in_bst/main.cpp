#include <iostream>
#include <stack>
#include <vector>
#include "bintree.h"

using namespace std;

class SolutionRecursive
{
public:
    int diff = INT_MAX;
    TreeNode *prev = nullptr;
    void inorderTraverse(TreeNode *node)
    {
        if (node == nullptr)
            return;

        inorderTraverse(node->left);

        if (prev != nullptr)
        {
            diff = min(diff, node->val - prev->val);
        }

        prev = node;
        inorderTraverse(node->right);
    }

    int getMinimumDifference(TreeNode *root)
    {
        inorderTraverse(root);
        return diff;
    }
};

class Solution
{
public:
    int getMinimumDifference(TreeNode *root)
    {
        int diff = INT_MAX;
        TreeNode *prev = nullptr;
        stack<TreeNode *> stk;
        stk.push(root);

        while (!stk.empty())
        {
            TreeNode *cur = stk.top();
            if (cur != nullptr)
            {
                stk.pop();

                if (cur->right)
                    stk.push(cur->right);

                stk.push(cur);
                stk.push(nullptr);

                if (cur->left)
                    stk.push(cur->left);
            }
            else
            {
                stk.pop();
                cur = stk.top();
                stk.pop();
                if (prev != nullptr)
                    diff = min(diff, cur->val - prev->val);
                prev = cur;
            }
        }

        return diff;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {4, 2, 6, 1, 3},
        {1, 0, 48, INT_MIN, INT_MIN, 12, 49},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(groups[group]);
    Solution s;
    cout << s.getMinimumDifference(root) << endl;

    return 0;
}
