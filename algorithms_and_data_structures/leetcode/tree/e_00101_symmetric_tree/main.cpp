#include <iostream>
#include <queue>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    bool compare(TreeNode *left, TreeNode *right)
    {
        if (left == nullptr && right == nullptr)
        {
            return true;
        }
        else if (left == nullptr || right == nullptr)
        {
            return false;
        }
        else if (left->val != right->val)
        {
            return false;
        }
        else
        {
            return compare(left->left, right->right) && compare(left->right, right->left);
        }
    }

    bool isSymmetric(TreeNode *root)
    {
        if (root == nullptr)
            return true;

        return compare(root->left, root->right);
    }
};

class SolutionIter
{
public:
    bool isSymmetric(TreeNode *root)
    {
        if (root == nullptr)
            return true;

        queue<TreeNode *> que;
        que.push(root->left);
        que.push(root->right);

        while (!que.empty())
        {
            TreeNode *left = que.front();
            que.pop();

            TreeNode *right = que.front();
            que.pop();

            if (!left && !right)
            {
                continue;
            }
            else if (!left || !right || (left->val != right->val))
            {
                return false;
            }

            que.push(left->left);
            que.push(right->right);
            que.push(left->right);
            que.push(right->left);
        }

        return true;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {1, 2, 2, 3, 4, 4, 3},
        {1, 2, 2, INT_MIN, 3, INT_MIN, 3},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;

    TreeNode *root = array2treeLevelOrder(groups[group - 1]);

    Solution s;
    cout << s.isSymmetric(root) << endl;

    return 0;
}
