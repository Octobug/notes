#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    int countNodes(TreeNode *root)
    {
        if (root == nullptr)
            return 0;

        TreeNode *left = root->left;
        TreeNode *right = root->right;
        int leftDepth = 0, rightDepth = 0;
        while (left)
        {
            left = left->left;
            leftDepth++;
        }

        while (left)
        {
            right = right->right;
            rightDepth++;
        }

        if (leftDepth == rightDepth)
        {
            return (2 << leftDepth) - 1;
        }

        return countNodes(root->left) + countNodes(root->right) + 1;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {1, 2, 3, 4, 5, 6},
        {},
        {1},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(groups[group]);
    Solution s;
    cout << s.countNodes(root) << endl;

    return 0;
}
