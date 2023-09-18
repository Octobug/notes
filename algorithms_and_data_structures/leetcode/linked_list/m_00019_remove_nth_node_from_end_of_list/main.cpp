#include <iostream>
#include <vector>
#include "linkedlist.h"

using namespace std;

class SolutionSpace
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        vector<ListNode *> ptrList;
        ListNode *dummy = new ListNode();
        dummy->next = head;
        ListNode *cur = dummy;

        while (cur)
        {
            ptrList.push_back(cur);
            cur = cur->next;
        }

        int idx = ptrList.size() - n;
        ptrList[idx - 1]->next = ptrList[idx]->next;

        return dummy->next;
    }
};

class Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode *slow = dummyHead;
        ListNode *fast = dummyHead;
        while (n-- && fast != nullptr)
            fast = fast->next;

        fast = fast->next;
        while (fast != nullptr)
        {
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;

        return dummyHead->next;
    }
};

int main()
{
    vector<int> list1 = {1, 2, 3, 4, 5}; // [1,2,3,5]
    vector<int> list2 = {1};             // []
    vector<int> list3 = {1, 2};          // [1]
    vector<vector<int>> groups = {list1, list2, list3};
    vector<int> ns = {2, 1, 1};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    ListNode *head = array2list(groups[group]);

    Solution s;
    ListNode *result = s.removeNthFromEnd(head, ns[group]);

    output(result);

    return 0;
}
