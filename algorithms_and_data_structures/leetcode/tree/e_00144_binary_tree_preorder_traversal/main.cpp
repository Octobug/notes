#include <iostream>
#include <stack>
#include <vector>
#include "array.h"
#include "bintree.h"

using namespace std;

class Solution
{
public:
    vector<int> preorderTraversal(TreeNode *root)
    {
        stack<TreeNode *> st;
        vector<int> result;
        if (root == nullptr)
            return result;

        st.push(root);
        while (!st.empty())
        {
            TreeNode *cur = st.top();
            st.pop();
            result.push_back(cur->val);
            if (cur->right)
                st.push(cur->right);
            if (cur->left)
                st.push(cur->left);
        }

        return result;
    }
};

class SolutionRecursive
{
public:
    void preTraverse(TreeNode *cur, vector<int> &result)
    {
        if (cur == nullptr)
        {
            return;
        }

        result.push_back(cur->val);
        preTraverse(cur->left, result);
        preTraverse(cur->right, result);
    }

    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> result;
        preTraverse(root, result);
        return result;
    }
};

int main()
{
    vector<int> input1 = {1, -1, 2, 3};
    vector<int> input2 = {};
    vector<int> input3 = {1};

    vector<vector<int>> groups = {input1, input2, input3};
    int group;

    cout << "Please input group: ";
    cin >> group;

    TreeNode *root = array2treeLevelOrder(groups[group - 1]);
    outputPreOrder(root);

    Solution s;
    vector<int> result = s.preorderTraversal(root);
    output(result);

    return 0;
}
