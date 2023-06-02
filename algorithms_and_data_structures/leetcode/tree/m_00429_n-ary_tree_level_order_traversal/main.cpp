#include <iostream>
#include <queue>
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
public:
    vector<vector<int>> levelOrder(Node *root)
    {
        vector<vector<int>> result;
        queue<Node *> q;

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
                Node *cur = q.front();
                q.pop();
                vec.push_back(cur->val);

                for (int j = 0; j < cur->children.size(); j++)
                {
                    q.push(cur->children[j]);
                }
            }
            result.push_back(vec);
        }

        return result;
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
    vector<vector<int>> result = s.levelOrder(root);

    output2d(result);

    return 0;
}
