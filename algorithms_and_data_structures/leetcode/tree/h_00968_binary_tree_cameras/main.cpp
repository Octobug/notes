#include <iostream>
#include <queue>
#include <vector>
#include "bintree.h"

using namespace std;

class Solution
{
private:
    const int UNCOVER = 0;
    const int CAMERA = 1;
    const int COVERED = 2;
    int result;

    int traverse(TreeNode *cur)
    {
        if (cur == NULL)
            return COVERED;

        int left = traverse(cur->left);
        int right = traverse(cur->right);

        if (left == COVERED && right == COVERED)
            return UNCOVER;

        else if (left == UNCOVER || right == UNCOVER)
        {
            result++;
            return CAMERA;
        }
        else if (left == CAMERA || right == CAMERA)
            return COVERED;

        return -1;
    }

public:
    int minCameraCover(TreeNode *root)
    {
        result = 0;
        if (traverse(root) == UNCOVER)
            result++;
        return result;
    }
};

int main()
{
    vector<vector<int>> inputs = {
        {0, 0, INT_MIN, 0, 0},                                  // 1
        {0, 0, INT_MIN, 0, INT_MIN, 0, INT_MIN, INT_MIN, 0},    // 2
        {0},                                                    // 1
        {0, 0, INT_MIN, INT_MIN, 0, 0, INT_MIN, INT_MIN, 0, 0}, // 2
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    TreeNode *root = array2treeLevelOrder(inputs[group]);
    Solution s;
    cout << s.minCameraCover(root) << endl;

    return 0;
}
