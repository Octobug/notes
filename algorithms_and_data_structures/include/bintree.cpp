#include <iostream>
#include <queue>
#include <vector>
#include "array.h"
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

void outputLevelOrder(TreeNode *root)
{
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
        int size = q.size();
        vector<int> vec;
        for (int i = 0; i < size; i++)
        {
            TreeNode *cur = q.front();
            q.pop();
            vec.push_back(cur->val);
            if (cur->left)
                q.push(cur->left);
            if (cur->right)
                q.push(cur->right);
        }
        output(vec);
    }
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
