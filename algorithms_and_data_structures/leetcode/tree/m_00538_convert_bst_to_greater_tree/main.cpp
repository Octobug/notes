#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    int sum = 0;
    void reverseInorder(TreeNode *node)
    {
        if (node->right)
            reverseInorder(node->right);

        node->val += sum;
        sum = node->val;

        if (node->left)
            reverseInorder(node->left);
    }

    TreeNode *convertBST(TreeNode *root)
    {
        if (root != nullptr)
            reverseInorder(root);
        return root;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {4, 1, 6, 0, 2, 5, 7, INT_MIN, INT_MIN, INT_MIN, 3, INT_MIN, INT_MIN, INT_MIN, 8},
        {0, INT_MIN, 1},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(groups[group]);
    Solution s;
    root = s.convertBST(root);
    outputLevelOrder(root);

    return 0;
}
