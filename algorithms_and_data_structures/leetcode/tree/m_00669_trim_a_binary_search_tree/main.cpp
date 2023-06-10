#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    TreeNode *trimBST(TreeNode *root, int low, int high)
    {
        TreeNode *cur = root;
        TreeNode **prev = nullptr;

        while (cur)
        {
            if (low == cur->val)
            {
                cur->left = nullptr;
                break;
            }
            else if (low < cur->val)
            {
                prev = &(cur->left);
                cur = cur->left;
            }
            else
            {
                if (prev != nullptr)
                    *prev = cur->right;
                else
                    root = cur->right;
                cur = cur->right;
            }
        }

        cur = root;
        prev = nullptr;

        while (cur)
        {
            if (high == cur->val)
            {
                cur->right = nullptr;
                break;
            }
            else if (high > cur->val)
            {
                prev = &(cur->right);
                cur = cur->right;
            }
            else
            {
                if (prev != nullptr)
                    *prev = cur->left;
                else
                    root = cur->left;
                cur = cur->left;
            }
        }

        return root;
    }
};

int main()
{
    vector<vector<vector<int>>> groups = {
        {{1, 0, 2}, {1, 2}},
        {{3, 0, 4, INT_MIN, 2, INT_MIN, INT_MIN, 1}, {1, 3}},
        {{3}, {2, 2}},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(groups[group][0]);
    Solution s;
    root = s.trimBST(root, groups[group][1][0], groups[group][1][1]);
    outputLevelOrder(root);

    return 0;
}
