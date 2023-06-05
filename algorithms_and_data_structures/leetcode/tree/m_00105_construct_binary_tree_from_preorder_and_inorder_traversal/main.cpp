#include <iostream>
#include <vector>
#include <bintree.h>

using namespace std;

class Solution
{
private:
    TreeNode *traversal(vector<int> &inorder, int inBegin, int inEnd, vector<int> &preorder, int preBegin, int preEnd)
    {
        if (preBegin == preEnd)
            return nullptr;

        int rootValue = preorder[preBegin];
        TreeNode *root = new TreeNode(rootValue);

        if (preEnd - preBegin == 1)
            return root;

        int delimiterIdx;
        for (delimiterIdx = inBegin; delimiterIdx < inEnd; delimiterIdx++)
        {
            if (inorder[delimiterIdx] == rootValue)
                break;
        }

        int leftInBegin = inBegin;
        int leftInEnd = delimiterIdx;
        int rightInBegin = delimiterIdx + 1;
        int rightInEnd = inEnd;

        int leftPreBegin = preBegin + 1;
        int leftPreEnd = preBegin + 1 + (delimiterIdx - inBegin);
        int rightPreBegin = preBegin + 1 + (delimiterIdx - inBegin);
        int rightPreEnd = preEnd;

        root->left = traversal(inorder, leftInBegin, leftInEnd, preorder, leftPreBegin, leftPreEnd);
        root->right = traversal(inorder, rightInBegin, rightInEnd, preorder, rightPreBegin, rightPreEnd);

        return root;
    }

public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        if (preorder.size() == 0 || inorder.size() == 0)
            return nullptr;

        return traversal(inorder, 0, inorder.size(), preorder, 0, preorder.size());
    }
};

int main()
{
    vector<vector<vector<int>>> groups = {
        {{3, 9, 20, 15, 7}, {9, 3, 15, 20, 7}},
        {{-1}, {-1}},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    TreeNode *root = s.buildTree(groups[group][0], groups[group][1]);

    outputLevelOrder(root);

    return 0;
}
