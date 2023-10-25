#include <iostream>
#include <vector>
#include "linkedlist.h"

using namespace std;

class Solution
{
public:
    int pairSum(ListNode *head)
    {
        int len = 0;
        ListNode *a = head;

        while (a)
        {
            a = a->next;
            len++;
        }

        int mid = len / 2;

        ListNode *b, *c;
        a = head;
        for (int i = 0; i < mid; i++)
            a = a->next;

        b = a->next;
        a->next = nullptr;
        while (b)
        {
            c = b->next;
            b->next = a;
            a = b;
            b = c;
        }

        int result = 0;
        b = head;
        while (a)
        {
            result = max(result, a->val + b->val);
            a = a->next;
            b = b->next;
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> heads = {
        {5, 4, 2, 1}, // 6
        {4, 2, 2, 3}, // 7
        {1, 100000},  // 100001
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    ListNode *head = array2list(heads[group]);

    Solution s;
    cout << s.pairSum(head) << endl;

    return 0;
}
