#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    int result = 0;
    int low, high;

    void inorder(TreeNode *node)
    {
        if (node->val > low && node->left)
            inorder(node->left);

        if (node->val >= low && node->val <= high)
            result += node->val;

        if (node->val < high && node->right)
            inorder(node->right);
    }

    int rangeSumBST(TreeNode *root, int l, int h)
    {
        low = l;
        high = h;
        inorder(root);
        return result;
    }
};

int main()
{
    vector<vector<int>> roots = {
        {10, 5, 15, 3, 7, INT_MIN, 18},           // 32
        {10, 5, 15, 3, 7, 13, 18, 1, INT_MIN, 6}, // 23
    };
    vector<int> lows = {7, 6};
    vector<int> highs = {15, 10};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(roots[group]);

    Solution s;
    cout << s.rangeSumBST(root, lows[group], highs[group]) << endl;

    return 0;
}
