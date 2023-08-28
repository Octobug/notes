#include <iostream>
#include <vector>
#include "linkedlist.h"

using namespace std;

class Solution
{
public:
    ListNode *swapPairs(ListNode *head)
    {
        if (!head || !head->next)
            return head;

        ListNode *pre = head;
        ListNode *cur = head->next;
        ListNode *nxt = cur->next;
        head = cur;

        while (cur)
        {
            cur->next = pre;

            if (nxt && nxt->next)
            {
                pre->next = nxt->next;
                pre = nxt;
                cur = nxt->next;
                nxt = cur->next;
            }
            else
            {
                pre->next = nxt;
                break;
            }
        }

        return head;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {1, 2, 3, 4}, // 2,1,4,3
        {},           //
        {1},          // 1
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    ListNode *head = array2list(groups[group]);
    Solution s;
    ListNode *result = s.swapPairs(head);
    output(result);

    return 0;
}
