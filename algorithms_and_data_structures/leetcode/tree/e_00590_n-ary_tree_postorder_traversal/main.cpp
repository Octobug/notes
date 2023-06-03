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
public:
    vector<int> postorder(Node *root)
    {
        vector<int> result;
        stack<Node *> st;

        if (root == nullptr)
        {
            return result;
        }

        st.push(root);
        while (!st.empty())
        {
            Node *cur = st.top();
            if (cur != nullptr)
            {
                st.pop();
                st.push(cur);
                st.push(nullptr);
                int childSize = cur->children.size();
                for (int i = childSize - 1; i >= 0; i--)
                {
                    st.push(cur->children[i]);
                }
            }
            else
            {
                st.pop();
                cur = st.top();
                st.pop();
                result.push_back(cur->val);
            }
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
    vector<int> result = s.postorder(root);

    output(result);

    return 0;
}
