#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    vector<int> nums;

    TreeNode *build(int iVal, int iBegin, int iEnd)
    {
        TreeNode *node = new TreeNode(nums[iVal]);

        int iRight = iBegin;
        while (iRight <= iEnd && nums[iRight] < nums[iVal])
            iRight++;

        if (iBegin < iRight)
            node->left = build(iBegin, iBegin + 1, iRight - 1);

        if (iRight <= iEnd)
            node->right = build(iRight, iRight + 1, iEnd);

        return node;
    }

    TreeNode *bstFromPreorder(vector<int> &preorder)
    {
        nums = preorder;
        return build(0, 1, preorder.size() - 1);
    }
};

int main()
{
    vector<vector<int>> preorders = {
        {8, 5, 1, 7, 10, 12}, // [8,5,10,1,7,null,12]
        {1, 3},               // [1,null,3]
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    TreeNode *root = s.bstFromPreorder(preorders[group]);
    outputLevelOrder(root);

    return 0;
}
