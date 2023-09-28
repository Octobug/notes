#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    int result = 0;

    pair<int, int> traverse(TreeNode *node)
    {
        int sum = node->val;
        int count = 1;

        if (node->left)
        {
            pair<int, int> res = traverse(node->left);
            sum += res.first;
            count += res.second;
        }

        if (node->right)
        {
            pair<int, int> res = traverse(node->right);
            sum += res.first;
            count += res.second;
        }

        if (node->val == sum / count)
            result++;

        return {sum, count};
    }

    int averageOfSubtree(TreeNode *root)
    {
        traverse(root);
        return result;
    }
};

int main()
{
    vector<vector<int>> roots = {
        {4, 8, 5, 0, 1, INT_MIN, 6},             // 5
        {1},                                     // 1
        {1, INT_MIN, 3, INT_MIN, 1, INT_MIN, 3}, // 1
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(roots[group]);

    Solution s;
    cout << s.averageOfSubtree(root) << endl;

    return 0;
}
