#include <iostream>
#include <vector>
#include "linkedlist.h"

using namespace std;

void output(ListNode *head)
{
    ListNode *p = head;
    while (p)
    {
        cout << p->val << "->";
        p = p->next;
    }
    cout << endl;
}

ListNode *array2list(vector<int> &arr)
{
    ListNode *head = nullptr;
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        ListNode *p = new ListNode(arr[i]);
        p->next = head;
        head = p;
    }
    return head;
}
