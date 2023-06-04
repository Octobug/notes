#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include "array.h"

using namespace std;

class Node
{
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};

Node *array2NTree(vector<int> &arr)
{
    if (!arr.size())
    {
        return nullptr;
    }

    int idx = 0;
    Node *root = new Node(arr[idx]);
    idx++;

    queue<Node *> q;
    q.push(root);

    while (idx < arr.size())
    {
        Node *cur = q.front();
        q.pop();
        idx++;

        while (idx < arr.size() && arr[idx] != INT_MIN)
        {
            Node *child = new Node(arr[idx]);
            cur->children.push_back(child);
            q.push(child);
            idx++;
        }
    }

    return root;
}

class Solution
{
    int getDepth(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        int childSize = node->children.size();
        int depth = 0;
        for (int i = 0; i < childSize; i++)
        {
            depth = max(depth, getDepth(node->children[i]));
        }
        return depth + 1;
    }

public:
    int maxDepth(Node *root)
    {
        return getDepth(root);
    }
};

int main()
{
    vector<vector<int>> groups = {
        {1, INT_MIN, 3, 2, 4, INT_MIN, 5, 6},
        {1, INT_MIN, 2, 3, 4, 5, INT_MIN, INT_MIN, 6, 7, INT_MIN, 8, INT_MIN, 9, 10, INT_MIN, INT_MIN, 11, INT_MIN, 12, INT_MIN, 13, INT_MIN, INT_MIN, 14},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;

    Node *root = array2NTree(groups[group - 1]);

    Solution s;
    cout << s.maxDepth(root) << endl;

    return 0;
}
