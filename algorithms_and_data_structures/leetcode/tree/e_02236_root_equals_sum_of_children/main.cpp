#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    bool checkTree(TreeNode *root)
    {
        return root->val == root->left->val + root->right->val;
    }
};

int main()
{
    vector<vector<int>> roots = {
        {10, 4, 6}, // 1
        {5, 3, 1},  // 0
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(roots[group]);

    Solution s;
    cout << s.checkTree(root) << endl;

    return 0;
}
