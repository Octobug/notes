#include <iostream>
#include <queue>
#include <vector>
#include "array.h"
#include "bintree.h"

using namespace std;

class Solution
{
public:
    vector<int> largestValues(TreeNode *root)
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
            int max = INT_MIN;
            int size = q.size();

            for (int i = 0; i < size; i++)
            {
                TreeNode *cur = q.front();
                q.pop();

                if (cur->val > max)
                {
                    max = cur->val;
                }

                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
            result.push_back(max);
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {1, 3, 2, 5, 3, INT_MIN, 9},
        {1, 2, 3},
        {0, -1},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;

    TreeNode *root = array2treeLevelOrder(groups[group - 1]);

    Solution s;
    vector<int> result = s.largestValues(root);

    output(result);

    return 0;
}
