#include <iostream>
#include <stack>
#include <vector>
#include "array.h"
#include "bintree.h"

using namespace std;

class Solution
{
public:
    vector<vector<int>> result;
    vector<int> path;
    void traversePath(TreeNode *node, int targetSum)
    {
        targetSum -= node->val;

        if (!node->left && !node->right && targetSum == 0)
        {
            result.push_back(path);
            return;
        }

        if (node->left)
        {
            path.push_back(node->left->val);
            traversePath(node->left, targetSum);
            path.pop_back();
        }

        if (node->right)
        {
            path.push_back(node->right->val);
            traversePath(node->right, targetSum);
            path.pop_back();
        }
    }

    vector<vector<int>> pathSum(TreeNode *root, int targetSum)
    {
        if (root == nullptr)
            return result;

        path.push_back(root->val);
        traversePath(root, targetSum);
        return result;
    }
};

int main()
{
    vector<vector<vector<int>>> groups = {
        {{5, 4, 8, 11, INT_MIN, 13, 4, 7, 2, INT_MIN, INT_MIN, 5, 1}, {22}},
        {{1, 2, 3}, {5}},
        {{1, 2}, {0}},
        {{}, {1}},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(groups[group][0]);
    Solution s;
    vector<vector<int>> result = s.pathSum(root, groups[group][1][0]);
    output2d(result);

    return 0;
}
