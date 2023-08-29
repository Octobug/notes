#include <iostream>
#include <vector>
#include "linkedlist.h"

using namespace std;

class Solution
{
public:
    bool isPalindrome(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return true;

        ListNode *slow = head, *fast = head, *pre = head;

        while (fast && fast->next)
        {
            pre = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        pre->next = nullptr;

        ListNode *a = slow, *b = slow->next, *c;
        a->next = nullptr;
        while (b)
        {
            c = b->next;
            b->next = a;
            a = b;
            b = c;
        }

        ListNode *left = head;
        ListNode *right = a;

        while (left)
        {
            if (left->val != right->val)
                return false;

            left = left->next;
            right = right->next;
        }

        return true;
    }
};

int main()
{
    vector<vector<int>> heads = {
        {1, 2, 2, 1},       // 1
        {1, 2},             // 0
        {1, 0, 3, 4, 0, 1}, // 0
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    ListNode *head = array2list(heads[group]);

    Solution s;
    cout << s.isPalindrome(head) << endl;

    return 0;
}
