#include <iostream>
#include <stack>
#include <vector>
#include "bintree.h"

using namespace std;

class SolutionRecursive1
{

public:
    bool isValid(TreeNode *node, long min, long max)
    {
        if (node == nullptr)
            return true;

        if (node->val <= min || node->val >= max)
            return false;

        return isValid(node->left, min, node->val) && isValid(node->right, node->val, max);
    }

    bool isValidBST(TreeNode *root)
    {
        return isValid(root, LONG_MIN, LONG_MAX);
    }
};

class SolutionRecursive2
{
public:
    TreeNode *pre = NULL;
    bool isValidBST(TreeNode *root)
    {
        if (root == NULL)
            return true;
        bool left = isValidBST(root->left);

        if (pre != NULL && pre->val >= root->val)
            return false;
        pre = root;

        bool right = isValidBST(root->right);
        return left && right;
    }
};

class Solution
{
public:
    bool isValidBST(TreeNode *root)
    {
        stack<TreeNode *> st;
        TreeNode *cur = root;
        TreeNode *pre = nullptr;

        while (cur != nullptr || !st.empty())
        {
            if (cur != nullptr)
            {
                st.push(cur);
                cur = cur->left;
            }
            else
            {
                cur = st.top();
                st.pop();
                if (pre != nullptr && pre->val >= cur->val)
                    return false;

                pre = cur;
                cur = cur->right;
            }
        }

        return true;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {2, 1, 3},
        {5, 1, 4, INT_MIN, INT_MIN, 3, 6},
        {5, 4, 6, INT_MIN, INT_MIN, 3, 7},
        {2, 2, 2},
        {2147483647},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(groups[group]);
    Solution s;
    cout << s.isValidBST(root) << endl;

    return 0;
}
