#include <iostream>
#include <vector>
#include <bintree.h>
#include <array.h>

using namespace std;

class Solution
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

int main()
{
    vector<int> input1 = {1, -1, 2, 3};
    vector<int> input2 = {};
    vector<int> input3 = {1};

    vector<vector<int>> groups = {input1, input2, input3};
    int group;

    cout << "Please input group: ";
    cin >> group;

    TreeNode *root = array2treePreOrder(groups[group - 1]);
    outputPreOrder(root);

    Solution s;
    vector<int> result = s.inorderTraversal(root);
    output(result);

    return 0;
}
