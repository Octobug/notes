#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    TreeNode *insertIntoBST(TreeNode *root, int val)
    {
        TreeNode *node = new TreeNode(val);

        if (root == nullptr)
            return node;

        TreeNode *cur = root;
        while (cur)
        {
            if (val > cur->val)
            {
                if (cur->right == nullptr)
                {
                    cur->right = node;
                    break;
                }
                cur = cur->right;
            }
            else if (val < cur->val)
            {
                if (cur->left == nullptr)
                {
                    cur->left = node;
                    break;
                }
                cur = cur->left;
            }
        }

        return root;
    }
};

int main()
{
    vector<vector<vector<int>>> groups = {
        {{4, 2, 7, 1, 3}, {5}},
        {{40, 20, 60, 10, 30, 50, 70}, {25}},
        {{4, 2, 7, 1, 3, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN}, {5}},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(groups[group][0]);
    Solution s;
    root = s.insertIntoBST(root, groups[group][1][0]);
    outputLevelOrder(root);

    return 0;
}
