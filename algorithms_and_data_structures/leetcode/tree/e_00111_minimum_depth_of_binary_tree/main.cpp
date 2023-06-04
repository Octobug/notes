#include <iostream>
#include <queue>
#include <vector>
#include "bintree.h"

using namespace std;

class SolutionIterative
{
public:
    int minDepth(TreeNode *root)
    {
        queue<TreeNode *> q;
        int depth = 0;

        if (root == nullptr)
        {
            return depth;
        }

        q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            depth++;

            for (int i = 0; i < size; i++)
            {
                TreeNode *cur = q.front();
                q.pop();

                if (cur->left == nullptr && cur->right == nullptr)
                    return depth;

                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
        }

        return depth;
    }
};

class Solution
{
    int getDepth(TreeNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        int left = getDepth(node->left);
        int right = getDepth(node->right);
        if (left == 0)
        {
            return right + 1;
        }
        else if (right == 0)
        {
            return left + 1;
        }
        else
        {
            return min(left, right) + 1;
        }
    }

public:
    int minDepth(TreeNode *root)
    {
        return getDepth(root);
    }
};

int main()
{
    vector<vector<int>> groups = {
        {3, 9, 20, INT_MIN, INT_MIN, 15, 7},
        {2, INT_MIN, 3, INT_MIN, 4, INT_MIN, 5, INT_MIN, 6},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;

    TreeNode *root = array2treeLevelOrder(groups[group - 1]);

    Solution s;
    cout << s.minDepth(root) << endl;

    return 0;
}
