#include <iostream>
#include <vector>
#include <bintree.h>

using namespace std;

class Solution
{
private:
    TreeNode *traversal(vector<int> &inorder, int inBegin, int inEnd, vector<int> &postorder, int postBegin, int postEnd)
    {
        if (postBegin == postEnd)
            return nullptr;

        int rootValue = postorder[postEnd - 1];
        TreeNode *root = new TreeNode(rootValue);

        if (postEnd - postBegin == 1)
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

        int leftPostBegin = postBegin;
        int leftPostEnd = postBegin + (delimiterIdx - inBegin);
        int rightPostBegin = postBegin + (delimiterIdx - inBegin);
        int rightPostEnd = postEnd - 1;

        root->left = traversal(inorder, leftInBegin, leftInEnd, postorder, leftPostBegin, leftPostEnd);
        root->right = traversal(inorder, rightInBegin, rightInEnd, postorder, rightPostBegin, rightPostEnd);

        return root;
    }

public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        if (inorder.size() == 0 || postorder.size() == 0)
            return nullptr;

        return traversal(inorder, 0, inorder.size(), postorder, 0, postorder.size());
    }
};

int main()
{
    vector<vector<vector<int>>> groups = {
        {{9, 3, 15, 20, 7}, {9, 15, 7, 20, 3}},
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
