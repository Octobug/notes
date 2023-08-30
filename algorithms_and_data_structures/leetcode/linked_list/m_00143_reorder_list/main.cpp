#include <iostream>
#include <vector>
#include "linkedlist.h"

using namespace std;

class Solution
{
public:
    void reorderList(ListNode *head)
    {
        if (!head->next)
            return;

        ListNode *slow = head, *fast = head, *leftTail;
        while (fast && fast->next)
        {
            leftTail = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        leftTail->next = nullptr;

        ListNode *a = slow, *b = slow->next, *c;
        a->next = nullptr;
        while (b)
        {
            c = b->next;
            b->next = a;
            a = b;
            b = c;
        }

        ListNode *p1 = head, *p2 = a;
        while (p1)
        {
            a = p1->next;
            b = p2->next;
            p1->next = p2;
            p1 = a;
            p2->next = a;
            c = p2;
            p2 = b;
        }

        if (b)
            c->next = b;
    }
};

int main()
{
    vector<vector<int>> heads = {
        {1, 2, 3, 4},    // 1,4,2,3
        {1, 2, 3, 4, 5}, // 1,5,2,4,3
        {1},             // 1
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    ListNode *head = array2list(heads[group]);

    Solution s;
    s.reorderList(head);
    output(head);

    return 0;
}
