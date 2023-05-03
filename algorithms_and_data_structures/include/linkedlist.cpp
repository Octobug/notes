#include <iostream>
#include <vector>
#include "linkedlist.h"

using namespace std;

void output(ListNode *head)
{
    ListNode *p = head->next;
    while (p)
    {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}

ListNode *array2list(vector<int> arr)
{
    ListNode *head = new ListNode();
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        ListNode *p = new ListNode(arr[i]);
        p->next = head->next;
        head->next = p;
    }
    return head;
}
