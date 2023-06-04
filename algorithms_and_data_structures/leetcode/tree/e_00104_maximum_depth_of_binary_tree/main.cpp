#include <iostream>
#include <queue>
#include <vector>
#include "bintree.h"

using namespace std;

class SolutionLevel
{
public:
    int maxDepth(TreeNode *root)
    {
        int result = 0;
        queue<TreeNode *> q;

        if (root == nullptr)
        {
            return result;
        }

        q.push(root);
        while (!q.empty())
        {
            int size = q.size();

            for (int i = 0; i < size; i++)
            {
                TreeNode *cur = q.front();
                q.pop();
                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
            result++;
        }

        return result;
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
        return max(left, right) + 1;
    }

public:
    int maxDepth(TreeNode *root)
    {
        return getDepth(root);
    }
};

int main()
{
    vector<vector<int>> groups = {
        {3, 9, 20, INT_MIN, INT_MIN, 15, 7},
        {1, INT_MIN, 2},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;

    TreeNode *root = array2treeLevelOrder(groups[group - 1]);

    Solution s;
    cout << s.maxDepth(root) << endl;

    return 0;
}
