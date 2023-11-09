#include <iostream>
#include <vector>
#include "array.h"
#include "bintree.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    void inorder(TreeNode *node, vector<int> &elems)
    {
        if (node->left)
            inorder(node->left, elems);

        elems.push_back(node->val);

        if (node->right)
            inorder(node->right, elems);
    };

    vector<int> getAllElements(TreeNode *root1, TreeNode *root2)
    {
        vector<int> elems1;
        vector<int> elems2;

        if (root1)
            inorder(root1, elems1);
        if (root2)
            inorder(root2, elems2);

        vector<int> result(elems1.size() + elems2.size(), 0);
        int index = 0;
        int idx1 = 0, idx2 = 0;

        while (idx1 < elems1.size() && idx2 < elems2.size())
        {
            if (elems1[idx1] < elems2[idx2])
                result[index++] = elems1[idx1++];
            else
                result[index++] = elems2[idx2++];
        }

        while (idx1 < elems1.size())
            result[index++] = elems1[idx1++];
        while (idx2 < elems2.size())
            result[index++] = elems2[idx2++];

        return result;
    }
};

int main()
{
    vector<vector<int>> root1s = {
        {2, 1, 4},       // [0,1,1,2,3,4]
        {1, INT_MIN, 8}, // [1,1,8,8]
        {},              //
    };
    vector<vector<int>> root2s = {
        {1, 0, 3},
        {8, 1},
        {5, 1, 7, 0, 2},
    };

    int group = getGroup();
    Solution s;
    TreeNode *root1 = array2treeLevelOrder(root1s[group]);
    TreeNode *root2 = array2treeLevelOrder(root2s[group]);

    vector<int> result = s.getAllElements(root1, root2);
    output(result);

    return 0;
}
