#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    int result = 0;

    void preorder(TreeNode *node, int sum)
    {
        if (!node->left && !node->right)
        {
            result += sum + node->val;
            return;
        }

        sum = (sum + node->val) * 10;
        if (node->left)
            preorder(node->left, sum);
        if (node->right)
            preorder(node->right, sum);
    }

    int sumNumbers(TreeNode *root)
    {
        preorder(root, 0);
        return result;
    }
};

int main()
{
    vector<vector<int>> roots = {
        {1, 2, 3},       // 25
        {4, 9, 0, 5, 1}, // 1026
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(roots[group]);

    Solution s;
    cout << s.sumNumbers(root) << endl;

    return 0;
}
