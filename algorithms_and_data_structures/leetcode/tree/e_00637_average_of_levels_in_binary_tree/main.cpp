#include <iostream>
#include <queue>
#include <vector>
#include "array.h"
#include "bintree.h"

using namespace std;

class Solution
{
public:
    vector<double> averageOfLevels(TreeNode *root)
    {
        vector<double> result;
        queue<TreeNode *> q;

        if (root == nullptr)
        {
            return result;
        }

        q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            double sum = 0;

            for (int i = 0; i < size; i++)
            {
                TreeNode *cur = q.front();
                q.pop();
                sum += cur->val;
                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
            result.push_back(sum / size);
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {3, 9, 20, INT_MIN, INT_MIN, 15, 7},
        {3, 9, 20, 15, 7},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;

    TreeNode *root = array2treePreOrder(groups[group - 1]);

    Solution s;
    vector<double> result = s.averageOfLevels(root);

    output(result);

    return 0;
}
