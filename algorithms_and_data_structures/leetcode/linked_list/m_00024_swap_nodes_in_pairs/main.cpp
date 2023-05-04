#include <iostream>
#include <vector>
#include <linkedlist.h>

using namespace std;

class Solution
{
public:
    ListNode *swapPairs(ListNode *head)
    {
        if (!head || !head->next)
        {
            return head;
        }

        ListNode *pre = head;
        ListNode *cur = head->next;
        ListNode *nxt = cur->next;
        head = cur;

        while (cur)
        {
            cur->next = pre;

            if (nxt)
            {
                if (nxt->next)
                {
                    pre->next = nxt->next;
                    pre = nxt;
                    cur = nxt->next;
                    nxt = cur->next;
                }
                else
                {
                    // three nodes
                    pre->next = nxt;
                    break;
                }
            }
            else
            {
                // two nodes
                pre->next = nullptr;
                break;
            }
        }

        return head;
    }
};

int main()
{
    vector<int> list1 = {1, 2, 3, 4};
    vector<int> list2 = {};
    vector<int> list3 = {1};

    vector<vector<int>> groups = {list1, list2, list3};
    int group;

    cout << "Please input group: ";
    cin >> group;

    ListNode *head = array2list(groups[group - 1]);

    Solution s;
    ListNode *result = s.swapPairs(head);
    output(result);
    return 0;
}
