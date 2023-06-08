#include <iostream>
#include <vector>
#include "array.h"
#include "bintree.h"

using namespace std;

class Solution
{
    vector<int> result;
    int maxCount = 0;
    int curCount = 0;
    int preVal = INT_MIN;

public:
    void find(TreeNode *node)
    {
        if (node->left)
            find(node->left);

        if (node->val == preVal)
            curCount++;
        else
            curCount = 1;

        if (curCount > maxCount)
        {
            maxCount = curCount;
            result.clear();
            result.push_back(node->val);
        }
        else if (curCount == maxCount)
        {
            result.push_back(node->val);
        }
        preVal = node->val;

        if (node->right)
            find(node->right);
    }

    vector<int> findMode(TreeNode *root)
    {
        find(root);
        return result;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {1, INT_MIN, 2, 2},
        {0},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(groups[group]);
    Solution s;
    vector<int> result = s.findMode(root);
    output(result);

    return 0;
}
