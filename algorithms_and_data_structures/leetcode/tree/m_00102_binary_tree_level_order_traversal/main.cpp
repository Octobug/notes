#include <iostream>
#include <queue>
#include <vector>
#include "array.h"
#include "bintree.h"

using namespace std;

class Solution
{
public:
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> result;
        queue<TreeNode *> q;

        if (root == nullptr)
        {
            return result;
        }

        q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            vector<int> vec;

            for (int i = 0; i < size; i++)
            {
                TreeNode *cur = q.front();
                q.pop();
                vec.push_back(cur->val);
                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
            result.push_back(vec);
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {3, 9, 20, INT_MIN, INT_MIN, 15, 7},
        {1},
        {},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;

    TreeNode *root = array2treePreOrder(groups[group - 1]);

    Solution s;
    vector<vector<int>> result = s.levelOrder(root);

    output2d(result);

    return 0;
}
