#include <iostream>
#include <stack>
#include <vector>
#include "array.h"
#include "bintree.h"

using namespace std;

class SolutionSelf
{
    vector<string> preTraverse(TreeNode *node)
    {
        if (!node->left && !node->right)
        {
            return {to_string(node->val)};
        }

        vector<string> result;
        if (node->left)
        {
            vector<string> leftPaths = preTraverse(node->left);
            for (int i = 0; i < leftPaths.size(); i++)
            {
                leftPaths[i] = to_string(node->val) + "->" + leftPaths[i];
            }
            result.insert(result.end(), leftPaths.begin(), leftPaths.end());
        }

        if (node->right)
        {
            vector<string> rightPaths = preTraverse(node->right);
            for (int i = 0; i < rightPaths.size(); i++)
            {
                rightPaths[i] = to_string(node->val) + "->" + rightPaths[i];
            }
            result.insert(result.end(), rightPaths.begin(), rightPaths.end());
        }

        return result;
    }

public:
    vector<string> binaryTreePaths(TreeNode *root)
    {
        if (root == nullptr)
            return {};

        return preTraverse(root);
    }
};

class SolutionRecursive
{
    void traversal(TreeNode *cur, string path, vector<string> &result)
    {
        path += to_string(cur->val);
        if (cur->left == nullptr && cur->right == nullptr)
        {
            result.push_back(path);
            return;
        }

        if (cur->left)
        {
            traversal(cur->left, path + "->", result);
        }
        if (cur->right)
        {
            traversal(cur->right, path + "->", result);
        }
    }

public:
    vector<string> binaryTreePaths(TreeNode *root)
    {
        vector<string> result;
        string path;

        if (root == nullptr)
            return result;

        traversal(root, path, result);
        return result;
    }
};

class Solution
{
public:
    vector<string> binaryTreePaths(TreeNode *root)
    {
        stack<TreeNode *> treeSt; // 保存树的遍历节点
        stack<string> pathSt;     // 保存遍历路径的节点
        vector<string> result;    // 保存最终路径集合

        if (root == nullptr)
            return result;

        treeSt.push(root);
        pathSt.push(to_string(root->val));

        while (!treeSt.empty())
        {
            TreeNode *node = treeSt.top();
            treeSt.pop(); // 取出节点 中

            string path = pathSt.top();
            pathSt.pop(); // 取出该节点对应的路径

            if (node->left == nullptr && node->right == nullptr)
            { // 叶子
                result.push_back(path);
            }

            if (node->right)
            { // 右
                treeSt.push(node->right);
                pathSt.push(path + "->" + to_string(node->right->val));
            }

            if (node->left)
            { // 左
                treeSt.push(node->left);
                pathSt.push(path + "->" + to_string(node->left->val));
            }
        }
        return result;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {1, 2, 3, INT_MIN, 5},
        {1},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;
    TreeNode *root = array2treeLevelOrder(groups[group]);

    Solution s;
    vector<string> result = s.binaryTreePaths(root);
    output(result);

    return 0;
}
