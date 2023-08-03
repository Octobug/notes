#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    pair<int, int> traverse(TreeNode *node)
    {
        pair<int, int> leftResult, rightResult;

        if (!node->left && !node->right)
            return {node->val, 0};

        if (node->left)
            leftResult = traverse(node->left);

        if (node->right)
            rightResult = traverse(node->right);

        int pickRoot = node->val + leftResult.second + rightResult.second;

        return {pickRoot, max(leftResult.first, leftResult.second) +
                              max(rightResult.first, rightResult.second)};
    }

    int rob(TreeNode *root)
    {
        pair<int, int> result = traverse(root);
        return max(result.first, result.second);
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {3, 2, 3, INT_MIN, 3, INT_MIN, 1},       // 7
        {3, 4, 5, 1, 3, INT_MIN, 1},             // 9
        {1, INT_MIN, 4, 3, INT_MIN, INT_MIN, 2}, // 6
        {1, 4, 5, 1, 1, INT_MIN, 100},           // 104
        {
            41, 37, 44, 24, 39, 42, 48, 1, 35, 38, 40, INT_MIN, 43, 46, 49, 0,
            2, 30, 36, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN,
            45, 47, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 4, 29, 32,
            INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 3, 9, 26,
            INT_MIN, 31, 34, INT_MIN, INT_MIN, 7, 11, 25, 27, INT_MIN, INT_MIN,
            33, INT_MIN, 6, 8, 10, 16, INT_MIN, INT_MIN, INT_MIN, 28, INT_MIN,
            INT_MIN, 5, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 15, 19,
            INT_MIN, INT_MIN, INT_MIN, INT_MIN, 12, INT_MIN, 18, 20, INT_MIN,
            13, 17, INT_MIN, INT_MIN, 22, INT_MIN, 14, INT_MIN, INT_MIN, 21,
            23}, // 690
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(inputs[group]);

    Solution s;
    cout << s.rob(root) << endl;

    return 0;
}
