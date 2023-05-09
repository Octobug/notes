#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

void preTraverse(TreeNode *cur)
{
    if (cur == nullptr)
        return;
    cout << cur->val << " "; // 中
    preTraverse(cur->left);  // 左
    preTraverse(cur->right); // 右
}

void outputPreOrder(TreeNode *root)
{
    preTraverse(root);
    cout << endl;
}

TreeNode *preCreate(vector<int> arr, int idx)
{
    if (idx >= arr.size() || arr[idx] == -1)
    {
        return nullptr;
    }

    TreeNode *node = new TreeNode(arr[idx++]);
    node->left = preCreate(arr, idx++);
    node->right = preCreate(arr, idx++);
    return node;
}

TreeNode *array2treePreOrder(vector<int> arr)
{
    return preCreate(arr, 0);
}
