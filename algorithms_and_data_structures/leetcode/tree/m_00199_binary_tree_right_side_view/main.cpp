#include <iostream>
#include <queue>
#include <vector>
#include "array.h"
#include "bintree.h"

using namespace std;

class Solution
{
public:
    vector<int> rightSideView(TreeNode *root)
    {
        vector<int> result;
        queue<TreeNode *> q;

        if (root == nullptr)
        {
            return result;
        }

        q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                TreeNode *cur = q.front();
                q.pop();

                if (i == size - 1)
                {
                    result.push_back(cur->val);
                };

                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {1, 2, 3, INT_MIN, 5, INT_MIN, 4},
        {1, INT_MIN, 3},
        {},
        {1, 2},
        {1, 2, 3, 4},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;

    TreeNode *root = array2treePreOrder(groups[group - 1]);

    Solution s;
    vector<int> result = s.rightSideView(root);

    output(result);

    return 0;
}
