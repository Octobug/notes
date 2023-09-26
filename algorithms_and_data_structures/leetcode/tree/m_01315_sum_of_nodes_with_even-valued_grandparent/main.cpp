#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    int result = 0;

    void traverse(TreeNode *node, bool pEven, bool gpEven)
    {
        if (gpEven)
            result += node->val;

        bool curEven = node->val % 2 == 0;

        if (node->left)
            traverse(node->left, curEven, pEven);

        if (node->right)
            traverse(node->right, curEven, pEven);
    }

    int sumEvenGrandparent(TreeNode *root)
    {
        traverse(root, false, false);
        return result;
    }
};

int main()
{
    vector<vector<int>> roots = {
        {6, 7, 8, 2, 7, 1, 3, 9, INT_MIN, 1, 4, INT_MIN, INT_MIN, INT_MIN,
         5}, // 18
        {1}, // 0
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(roots[group]);

    Solution s;
    cout << s.sumEvenGrandparent(root) << endl;

    return 0;
}
