#include <iostream>
#include <queue>
#include <vector>
#include "bintree.h"

using namespace std;

class SolutionRecursive
{
public:
    TreeNode *build(vector<int> &nums, int begin, int end)
    {
        if (begin > end)
            return nullptr;

        int mid = (begin + end) / 2;
        TreeNode *node = new TreeNode(nums[mid]);

        node->left = build(nums, begin, mid - 1);
        node->right = build(nums, mid + 1, end);

        return node;
    }

    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        return build(nums, 0, nums.size() - 1);
    }
};

class Solution
{
public:
    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        if (nums.size() == 0)
            return nullptr;

        TreeNode *root = new TreeNode(0); // 初始根节点
        queue<TreeNode *> nodeQue;        // 放遍历的节点
        queue<int> leftQue;               // 保存左区间下标
        queue<int> rightQue;              // 保存右区间下标
        nodeQue.push(root);               // 根节点入队列
        leftQue.push(0);                  // 0为左区间下标初始位置
        rightQue.push(nums.size() - 1);   // nums.size() - 1为右区间下标初始位置

        while (!nodeQue.empty())
        {
            TreeNode *curNode = nodeQue.front();
            nodeQue.pop();

            int left = leftQue.front();
            leftQue.pop();
            int right = rightQue.front();
            rightQue.pop();

            int mid = (left + right) / 2;
            curNode->val = nums[mid];

            if (left <= mid - 1)
            {
                curNode->left = new TreeNode(0);
                nodeQue.push(curNode->left);
                leftQue.push(left);
                rightQue.push(mid - 1);
            }

            if (right >= mid + 1)
            {
                curNode->right = new TreeNode(0);
                nodeQue.push(curNode->right);
                leftQue.push(mid + 1);
                rightQue.push(right);
            }
        }
        return root;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {-10, -3, 0, 5, 9},
        {1, 3},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    TreeNode *root = s.sortedArrayToBST(groups[group]);
    outputLevelOrder(root);

    return 0;
}
