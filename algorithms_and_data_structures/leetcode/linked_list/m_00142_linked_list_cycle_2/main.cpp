#include <iostream>
#include <vector>
#include "linkedlist.h"

using namespace std;

class Solution
{
public:
    ListNode *detectCycle(ListNode *head)
    {
        ListNode *fast = head;
        ListNode *slow = head;

        while (fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;

            if (fast == slow)
            {
                ListNode *idx1 = head;
                ListNode *idx2 = fast;
                while (idx1 != idx2)
                {
                    idx1 = idx1->next;
                    idx2 = idx2->next;
                }
                return idx1;
            }
        }

        return nullptr;
    }
};

int main()
{
    vector<int> list1 = {3, 2, 0, -4};
    vector<int> list2 = {1, 2};

    vector<vector<int>> groups = {list1, list2};
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    ListNode *head = array2list(groups[group - 1]);

    int pos;
    cout << "Please input pos: ";
    cin >> pos;

    ListNode *p = head->next;
    while (pos--)
    {
        p = p->next;
    }
    ListNode *pentry = p;
    while (p->next)
    {
        p = p->next;
    }
    p->next = pentry;

    Solution s;
    ListNode *entry = s.detectCycle(head);
    cout << entry->val << endl;

    return 0;
}
