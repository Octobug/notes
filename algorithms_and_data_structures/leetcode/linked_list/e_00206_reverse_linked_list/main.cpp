#include <iostream>
#include "linkedlist.h"

using namespace std;

// iteratively
class Solution1
{
public:
    ListNode *reverseList(ListNode *head)
    {
        if (!head || !head->next)
            return head;

        ListNode *a = head;
        ListNode *b = a->next;
        ListNode *c;

        a->next = nullptr;
        while (b)
        {
            c = b->next;
            b->next = a;
            a = b;
            b = c;
        }

        return a;
    }
};

// recursively
class Solution2
{
public:
    ListNode *reverseList(ListNode *head)
    {
        if (!head || !head->next)
            return head;

        ListNode *first = head;
        ListNode *remains = reverseList(first->next);

        first->next->next = first;
        first->next = nullptr;
        return remains;
    }
};

int main()
{
    vector<int> list1 = {1, 2, 3, 4, 5};
    vector<int> list2 = {1, 2};
    vector<int> list3 = {};

    vector<vector<int>> groups = {list1, list2, list3};
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution1 s1;
    Solution2 s2;

    ListNode *head1 = array2list(groups[group]);
    ListNode *head2 = array2list(groups[group]);

    ListNode *newHead1 = s1.reverseList(head1);
    ListNode *newHead2 = s2.reverseList(head2);

    output(newHead1);
    output(newHead2);

    return 0;
}
