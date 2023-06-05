#include <iostream>
#include <stack>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    bool hasPathSum(TreeNode *root, int sum)
    {
        if (root == nullptr)
            return false;

        stack<pair<TreeNode *, int>> st;
        st.push(pair<TreeNode *, int>(root, root->val));
        while (!st.empty())
        {
            pair<TreeNode *, int> node = st.top();
            st.pop();

            if (!node.first->left && !node.first->right && sum == node.second)
                return true;

            if (node.first->right)
            {
                st.push(pair<TreeNode *, int>(node.first->right, node.second + node.first->right->val));
            }

            if (node.first->left)
            {
                st.push(pair<TreeNode *, int>(node.first->left, node.second + node.first->left->val));
            }
        }
        return false;
    }
};

class SolutionRecursive
{
public:
    bool checkSum(TreeNode *node, int targetSum)
    {
        targetSum -= node->val;

        if (!node->left && !node->right)
            return targetSum == 0;
        else if (node->left && checkSum(node->left, targetSum))
            return true;
        else if (node->right && checkSum(node->right, targetSum))
            return true;
        else
            return false;
    }

    bool hasPathSum(TreeNode *root, int targetSum)
    {
        if (root == nullptr)
            return false;
        return checkSum(root, targetSum);
    }
};

int main()
{
    vector<vector<vector<int>>> groups = {
        {{5, 4, 8, 11, INT_MIN, 13, 4, 7, 2, INT_MIN, INT_MIN, INT_MIN, 1}, {22}},
        {{1, 2, 3}, {5}},
        {{}, {0}},
        {{1, 2}, {1}},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(groups[group][0]);
    Solution s;
    cout << s.hasPathSum(root, groups[group][1][0]) << endl;

    return 0;
}
