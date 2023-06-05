#include <iostream>
#include <queue>
#include <vector>
#include "array.h"
#include "bintree.h"

using namespace std;

class SolutionIteration
{
public:
    int findBottomLeftValue(TreeNode *root)
    {
        queue<TreeNode *> q;

        q.push(root);
        int leftmost = q.front()->val;
        while (!q.empty())
        {
            leftmost = q.front()->val;
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
        }

        return leftmost;
    }
};

class Solution
{
public:
    int maxDepth = INT_MIN;
    int result;

    void traversal(TreeNode *root, int depth)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            if (depth > maxDepth)
            {
                maxDepth = depth;
                result = root->val;
            }
            return;
        }

        if (root->left)
        {
            traversal(root->left, depth + 1);
        }
        if (root->right)
        {
            traversal(root->right, depth + 1);
        }
    }

    int findBottomLeftValue(TreeNode *root)
    {
        traversal(root, 0);
        return result;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {2, 1, 3},
        {1, 2, 3, 4, INT_MIN, 5, 6, INT_MIN, INT_MIN, 7},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(groups[group]);

    Solution s;
    cout << s.findBottomLeftValue(root) << endl;

    return 0;
}
