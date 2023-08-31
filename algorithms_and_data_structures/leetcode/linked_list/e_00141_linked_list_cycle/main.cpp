#include <iostream>
#include <vector>
#include "linkedlist.h"

using namespace std;

class SolutionChanged
{
public:
    bool hasCycle(ListNode *head)
    {
        ListNode *p = head;

        while (p)
        {
            if (p->val == INT_MIN)
                return true;

            p->val = INT_MIN;
            p = p->next;
        }

        return false;
    }
};

class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        ListNode *fast = head;
        ListNode *slow = head;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast)
                return true;
        }

        return false;
    }
};

int main()
{
    vector<vector<int>> heads = {
        {3, 2, 0, -4}, // 1
        {1, 2},        // 0
        {1},           // 0
    };
    vector<int> poss = {1, 0, -1};
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    ListNode *head = array2list(heads[group]);
    ListNode *p = head, *q;

    if (poss[group] >= 0)
    {
        for (int i = 0; i < poss[group]; i++)
            p = p->next;

        q = p;

        while (q->next)
            q = q->next;

        q->next = p;
    }

    Solution s;
    cout << s.hasCycle(head) << endl;

    return 0;
}
