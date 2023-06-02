#include <iostream>
#include <stack>
#include <vector>
#include "array.h"
#include "bintree.h"

using namespace std;

class SolutionRecursive
{
public:
    void postTraverse(TreeNode *cur, vector<int> &result)
    {
        if (cur == nullptr)
        {
            return;
        }

        postTraverse(cur->left, result);
        postTraverse(cur->right, result);
        result.push_back(cur->val);
    }

    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> result;
        postTraverse(root, result);
        return result;
    }
};

class Solution
{
public:
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> result;
        stack<TreeNode *> st;
        if (root == nullptr)
            return result;
        st.push(root);

        while (!st.empty())
        {
            TreeNode *cur = st.top();
            st.pop();
            result.push_back(cur->val);

            if (cur->left != nullptr)
                st.push(cur->left);
            if (cur->right != nullptr)
                st.push(cur->right);
        }
        reverse(result.begin(), result.end());

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
    vector<int> result = s.postorderTraversal(root);
    output(result);

    return 0;
}
