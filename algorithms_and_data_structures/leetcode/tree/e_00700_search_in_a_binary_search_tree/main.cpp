#include <iostream>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    TreeNode *searchBST(TreeNode *root, int val)
    {
        TreeNode *cur = root;
        while (cur)
        {
            if (cur->val == val)
                return cur;
            else if (cur->val > val)
                cur = cur->left;
            else
                cur = cur->right;
        }
        return nullptr;
    }
};

int main()
{
    vector<vector<vector<int>>> groups = {
        {{4, 2, 7, 1, 3}, {2}},
        {{4, 2, 7, 1, 3}, {5}},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(groups[group][0]);
    Solution s;
    TreeNode *result = s.searchBST(root, groups[group][1][0]);
    outputLevelOrder(result);

    return 0;
}
