#include <iostream>
#include <stack>
#include <vector>
#include "array.h"
#include "bintree.h"

using namespace std;

class SolutionRecursive
{
public:
    void inTraverse(TreeNode *cur, vector<int> &result)
    {
        if (cur == nullptr)
        {
            return;
        }

        inTraverse(cur->left, result);
        result.push_back(cur->val);
        inTraverse(cur->right, result);
    }

    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> result;
        inTraverse(root, result);
        return result;
    }
};

class Solution
{
public:
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> result;
        stack<TreeNode *> st;
        TreeNode *cur = root;
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
                result.push_back(cur->val);
                cur = cur->right;
            }
        }

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
    vector<int> result = s.inorderTraversal(root);
    output(result);

    return 0;
}
