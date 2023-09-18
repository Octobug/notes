#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    int maxDepth = 0;
    int sum = 0;

    void traverse(TreeNode *node, int depth)
    {
        if (depth > maxDepth)
        {
            maxDepth = depth;
            sum = 0;
        }

        if (depth == maxDepth)
            sum += node->val;
        if (node->left)
            traverse(node->left, depth + 1);
        if (node->right)
            traverse(node->right, depth + 1);
    }

    int deepestLeavesSum(TreeNode *root)
    {
        if (root)
            traverse(root, 1);

        return sum;
    }
};

int main()
{
    int MIN = INT_MIN;
    vector<vector<int>> roots = {
        {1, 2, 3, 4, 5, MIN, 6, 7, MIN, MIN, MIN, MIN, 8},     // 15
        {6, 7, 8, 2, 7, 1, 3, 9, MIN, 1, 4, MIN, MIN, MIN, 5}, // 19
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(roots[group]);
    Solution s;
    cout << s.deepestLeavesSum(root) << endl;

    return 0;
}
