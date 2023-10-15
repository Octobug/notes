#include <iostream>
#include <unordered_map>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
public:
    unordered_map<int, vector<TreeNode *>> umap;

    vector<TreeNode *> allPossibleFBT(int n)
    {
        if (umap.find(n) != umap.end())
            return umap[n];

        if (n == 1)
        {
            TreeNode *node = new TreeNode(0);
            return {node};
        }

        vector<TreeNode *> result;
        for (int left = 1, right = n - 2; left < n; left += 2, right -= 2)
        {
            vector<TreeNode *> subtreesL = allPossibleFBT(left);
            vector<TreeNode *> subtreesR = allPossibleFBT(right);
            for (auto l : subtreesL)
            {
                for (auto r : subtreesR)
                {
                    TreeNode *node = new TreeNode(0);
                    node->left = l;
                    node->right = r;
                    result.push_back(node);
                }
            }
        }

        umap[n] = result;
        return result;
    }
};

int main()
{
    cout << "Please input n: ";
    int n;
    cin >> n;

    Solution s;
    vector<TreeNode *> result = s.allPossibleFBT(n);

    for (int i = 0; i < result.size(); i++)
    {
        outputLevelOrder(result[i]);
        cout << "================" << endl;
    }

    return 0;
}
