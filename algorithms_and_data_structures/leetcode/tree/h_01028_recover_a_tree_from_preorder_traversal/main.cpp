#include <iostream>
#include <vector>
#include "bintree.h"
#include "input.h"

using namespace std;

class Solution
{
public:
    string str;
    int index = 0;
    int validIndex = 0;

    TreeNode *preorder(int expDepth)
    {
        int depth = 0;
        validIndex = index;
        while (index < str.size() && str[index] == '-')
        {
            index++;
            depth++;
        }

        if (depth < expDepth)
        {
            index = validIndex;
            return nullptr;
        }

        int numBegin = index;
        while (index < str.size() && str[index] != '-')
            index++;

        int val = stoi(str.substr(numBegin, index - numBegin));
        TreeNode *node = new TreeNode(val);

        if (index >= str.size())
            return node;

        node->left = preorder(expDepth + 1);
        node->right = preorder(expDepth + 1);

        return node;
    }

    TreeNode *recoverFromPreorder(string traversal)
    {
        str = traversal;
        return preorder(0);
    }
};

int main()
{
    vector<string> traversals = {
        "1-2--3--4-5--6--7",   // [1,2,5,3,4,6,7]
        "1-2--3---4-5--6---7", // [1,2,5,3,null,6,null,4,null,7]
        "1-401--349---90--88", // [1,401,null,349,88,90]
    };

    int group = getGroup();
    Solution s;
    TreeNode *root = s.recoverFromPreorder(traversals[group]);
    outputLevelOrder(root);

    return 0;
}
