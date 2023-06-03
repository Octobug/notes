#ifndef __BINTREE__
#define __BINTREE__

#include <vector>

using namespace std;

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

void outputPreOrder(TreeNode *root);
void outputLevelOrder(TreeNode *root);
TreeNode *array2treeLevelOrder(vector<int> arr);

#endif
