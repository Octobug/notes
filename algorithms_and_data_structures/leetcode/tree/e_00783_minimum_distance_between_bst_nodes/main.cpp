#include <iostream>
#include <stack>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
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

    int minDiffInBST(TreeNode *root)
    {
        inorderTraverse(root);
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
    cout << s.minDiffInBST(root) << endl;

    return 0;
}
