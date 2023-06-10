#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    TreeNode *deleteNode(TreeNode *root, int key)
    {
        if (root == nullptr)
            return nullptr;

        TreeNode *cur = root;
        TreeNode **prev = nullptr;
        TreeNode **toDelPrev = nullptr;

        while (cur)
        {
            if (key < cur->val)
            {
                prev = &(cur->left);
                toDelPrev = &(cur->left);
                cur = cur->left;
            }
            else if (key > cur->val)
            {
                prev = &(cur->right);
                toDelPrev = &(cur->right);
                cur = cur->right;
            }
            else
            {
                TreeNode *toDel = cur;

                if (cur->left == nullptr && cur->right == nullptr)
                {
                    if (prev != nullptr)
                        *prev = nullptr;
                    else
                        root = nullptr;
                }
                else
                {
                    if (cur->left)
                    {
                        prev = &(cur->left);
                        cur = cur->left;
                        while (cur->right)
                        {
                            prev = &(cur->right);
                            cur = cur->right;
                        }
                        if (prev != nullptr)
                            *prev = cur->left;
                    }
                    else if (cur->right)
                    {
                        prev = &(cur->right);
                        cur = cur->right;
                        while (cur->left)
                        {
                            prev = &(cur->left);
                            cur = cur->left;
                        }
                        if (prev != nullptr)
                            *prev = cur->right;
                    }

                    if (toDelPrev != nullptr)
                        *toDelPrev = cur;
                    else
                        root = cur;
                    cur->left = toDel->left;
                    cur->right = toDel->right;
                }

                delete toDel;
                break;
            }
        }

        return root;
    }
};

int main()
{
    vector<vector<vector<int>>> groups = {
        {{5, 3, 6, 2, 4, INT_MIN, 7}, {3}},
        {{5, 3, 6, 2, 4, INT_MIN, 7}, {0}},
        {{}, {0}},
        {{0}, {0}},
        {{5, 3, 6, 2, 4, INT_MIN, 7}, {7}},
        {{1, INT_MIN, 2}, {1}},
        {{5, 3, 6, 1, 4, INT_MIN, INT_MIN, INT_MIN, 2}, {3}},
        {{2, 0, 34, INT_MIN, 1, 25, 40, INT_MIN, INT_MIN, 11, 31, 35, 45, 10, 18, 29, 32, INT_MIN, 36, 43, 46, 4, INT_MIN, 12, 24, 26, 30, INT_MIN, INT_MIN, INT_MIN, 39, 42, 44, INT_MIN, 48, 3, 9, INT_MIN, 14, 22, INT_MIN, INT_MIN, 27, INT_MIN, INT_MIN, 38, INT_MIN, 41, INT_MIN, INT_MIN, INT_MIN, 47, 49, INT_MIN, INT_MIN, 5, INT_MIN, 13, 15, 21, 23, INT_MIN, 28, 37, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 8, INT_MIN, INT_MIN, INT_MIN, 17, 19, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 7, INT_MIN, 16, INT_MIN, INT_MIN, 20, 6}, {33}},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(groups[group][0]);
    Solution s;
    root = s.deleteNode(root, groups[group][1][0]);
    outputLevelOrder(root);

    return 0;
}
