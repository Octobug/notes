#include <iostream>
#include <queue>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        if (p == nullptr && q == nullptr)
            return true;

        queue<TreeNode *> que;
        que.push(p);
        que.push(q);

        while (!que.empty())
        {
            TreeNode *pnode = que.front();
            que.pop();

            TreeNode *qnode = que.front();
            que.pop();

            if (!pnode && !qnode)
            {
                continue;
            }
            else if (!pnode || !qnode || (pnode->val != qnode->val))
            {
                return false;
            }

            que.push(pnode->left);
            que.push(qnode->left);
            que.push(pnode->right);
            que.push(qnode->right);
        }

        return true;
    }
};

int main()
{
    vector<vector<vector<int>>> groups = {
        {{1, 2, 3}, {1, 2, 3}},
        {{1, 2}, {1, INT_MIN, 2}},
        {{1, 2, 1}, {1, 1, 2}},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *p = array2treeLevelOrder(groups[group][0]);
    TreeNode *q = array2treeLevelOrder(groups[group][1]);

    Solution s;
    cout << s.isSameTree(p, q) << endl;

    return 0;
}
