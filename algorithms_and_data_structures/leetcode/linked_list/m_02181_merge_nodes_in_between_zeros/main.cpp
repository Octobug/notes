#include <iostream>
#include <vector>
#include "linkedlist.h"

using namespace std;

class Solution
{
public:
    ListNode *mergeNodes(ListNode *head)
    {
        ListNode *mp = head, *p = head->next;

        while (p->next)
        {
            if (p->val == 0)
            {
                mp = p;
            }
            else
            {
                mp->val += p->val;
                mp->next = p->next;
            }

            p = p->next;
        }

        mp->next = nullptr;

        return head;
    }
};

int main()
{
    vector<vector<int>> heads = {
        {0, 3, 1, 0, 4, 5, 2, 0}, // [4,11]
        {0, 1, 0, 3, 0, 2, 2, 0}, // [1,3,4]
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    ListNode *head = array2list(heads[group]);
    Solution s;
    head = s.mergeNodes(head);
    output(head);

    return 0;
}
