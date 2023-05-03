#include <iostream>
#include <vector>
#include "linkedlist.h"

using namespace std;

class Solution
{
public:
    ListNode *removeElements(ListNode *head, int val)
    {
        while (head && head->val == val)
        {
            ListNode *tmp = head;
            head = head->next;
            delete tmp;
        }

        ListNode *p = head;
        while (p)
        {
            if (p->next && p->next->val == val)
            {
                ListNode *tmp = p->next;
                p->next = p->next->next;
                delete tmp;
            }
            else
            {
                p = p->next;
            }
        }

        return head;
    }
};

int main()
{
    vector<int> head1 = {1, 2, 6, 3, 4, 5, 6};
    vector<int> head2 = {};
    vector<int> head3 = {7, 7, 7, 7};
    vector<int> head4 = {1, 2};
    vector<vector<int>> groups = {head1, head2, head3, head4};

    int group;
    cout << "Please input group: ";
    cin >> group;

    int val;
    cout << "Please input val: ";
    cin >> val;

    ListNode *head = array2list(groups[group - 1]);

    Solution s;
    ListNode *new_head = s.removeElements(head, val);

    output(new_head);

    return 0;
}
