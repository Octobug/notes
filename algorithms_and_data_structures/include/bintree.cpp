#include <iostream>
#include <queue>
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

TreeNode *array2treeLevelOrder(vector<int> arr)
{
    if (arr.empty())
        return nullptr;

    int idx = 0;
    TreeNode *root = new TreeNode(arr[idx]);
    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *cur = q.front();
        q.pop();
        idx++;
        if (idx >= arr.size())
        {
            break;
        }
        if (arr[idx] != INT_MIN)
        {
            cur->left = new TreeNode(arr[idx]);
            q.push(cur->left);
        }

        idx++;
        if (idx >= arr.size())
        {
            break;
        }
        if (arr[idx] != INT_MIN)
        {
            cur->right = new TreeNode(arr[idx]);
            q.push(cur->right);
        }
    }

    return root;
}
