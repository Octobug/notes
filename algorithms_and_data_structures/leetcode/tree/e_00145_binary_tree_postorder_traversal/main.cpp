#include <iostream>
#include <vector>
#include <bintree.h>
#include <array.h>

using namespace std;

class Solution
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
    vector<int> result = s.postorderTraversal(root);
    output(result);

    return 0;
}
