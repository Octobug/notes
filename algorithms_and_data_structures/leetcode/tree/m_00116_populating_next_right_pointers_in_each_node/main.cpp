#include <iostream>
#include <queue>
#include <vector>
#include "array.h"

using namespace std;

class Node
{
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

void outputLevelOrder(Node *root)
{
    queue<Node *> q;

    if (root == nullptr)
    {
        return;
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
            if (cur->left)
                q.push(cur->left);
            if (cur->right)
                q.push(cur->right);
        }
        output(vec);
    }
}

Node *arr2treeLevelOrder(vector<int> arr)
{
    if (arr.empty())
        return nullptr;

    int idx = 0;
    Node *root = new Node(arr[idx]);
    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *cur = q.front();
        q.pop();
        idx++;
        if (idx >= arr.size())
        {
            break;
        }
        if (arr[idx] != INT_MIN)
        {
            cur->left = new Node(arr[idx]);
            q.push(cur->left);
        }

        idx++;
        if (idx >= arr.size())
        {
            break;
        }
        if (arr[idx] != INT_MIN)
        {
            cur->right = new Node(arr[idx]);
            q.push(cur->right);
        }
    }

    return root;
}

class Solution
{
public:
    Node *connect(Node *root)
    {
        queue<Node *> q;

        if (root == nullptr)
        {
            return nullptr;
        }

        q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            vector<Node *> vec;

            for (int i = 0; i < size; i++)
            {
                Node *cur = q.front();
                q.pop();
                vec.push_back(cur);
                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
                if (i > 0 && i < size)
                {
                    vec[i - 1]->next = vec[i];
                }
            }
        }

        return root;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {1, 2, 3, 4, 5, 6, 7},
        {},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;

    Node *root = arr2treeLevelOrder(groups[group - 1]);

    Solution s;
    Node *result = s.connect(root);
    cout << "succ: " << endl;
    outputLevelOrder(result);

    return 0;
}
