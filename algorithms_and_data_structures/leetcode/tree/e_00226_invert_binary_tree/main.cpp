#include <iostream>
#include <stack>
#include <vector>
#include "bintree.h"

using namespace std;

class SolutionRecursive
{
public:
    TreeNode *invertTree(TreeNode *root)
    {
        preSwitch(root);
        return root;
    }

    TreeNode *preSwitch(TreeNode *node)
    {
        if (node == nullptr)
            return nullptr;
        swap(node->left, node->right);
        preSwitch(node->left);
        preSwitch(node->right);
        return node;
    }
};

class Solution
{
public:
    TreeNode *invertTree(TreeNode *root)
    {
        stack<TreeNode *> st;
        if (root != nullptr)
            st.push(root);
        while (!st.empty())
        {
            TreeNode *node = st.top();
            if (node != nullptr)
            {
                st.pop();
                if (node->right)
                    st.push(node->right); // 右
                if (node->left)
                    st.push(node->left); // 左
                st.push(node);           // 中
                st.push(nullptr);
            }
            else
            {
                st.pop(); // 去掉 null 标记
                node = st.top();
                st.pop();
                swap(node->left, node->right);
            }
        }
        return root;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {4, 2, 7, 1, 3, 6, 9},
        {2, 1, 3},
        {},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;

    Solution s;
    TreeNode *result = s.invertTree(array2treeLevelOrder(groups[group - 1]));
    outputLevelOrder(result);

    return 0;
}
