#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
    int getDepth(TreeNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        int left = getDepth(node->left);
        if (left == -1)
            return -1;

        int right = getDepth(node->right);
        if (right == -1)
            return -1;

        return abs(left - right) > 1 ? -1 : max(left, right) + 1;
    }

public:
    bool isBalanced(TreeNode *root)
    {
        return getDepth(root) != -1;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {3, 9, 20, INT_MIN, INT_MIN, 15, 7},
        {1, 2, 2, 3, 3, INT_MIN, INT_MIN, 4, 4},
        {},
        {1, 2, 2, 3, INT_MIN, INT_MIN, 3, 4, INT_MIN, INT_MIN, 4},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;
    TreeNode *root = array2treeLevelOrder(groups[group]);

    Solution s;
    cout << s.isBalanced(root) << endl;

    return 0;
}
