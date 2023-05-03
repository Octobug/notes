#ifndef __LINKEDLIST__
#define __LINKEDLIST__

#include <vector>

using namespace std;

// Definition for singly-linked list.
// Leetcode 中的链表没有空头结点
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void output(ListNode *head);
ListNode *array2list(vector<int> arr);

#endif
