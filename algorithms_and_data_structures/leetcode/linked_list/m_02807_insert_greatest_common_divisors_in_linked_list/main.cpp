#include <iostream>
#include <vector>
#include "linkedlist.h"

using namespace std;

class SolutionRecursive
{
public:
    int getGCD(int a, int b)
    {
        if (b == 0)
            return a;

        return getGCD(b, a % b);
    }

    ListNode *insertGreatestCommonDivisors(ListNode *head)
    {
        if (!head || !head->next)
            return head;

        insertGreatestCommonDivisors(head->next);

        int gcd = getGCD(head->val, head->next->val);
        ListNode *mid = new ListNode(gcd);
        mid->next = head->next;
        head->next = mid;

        return head;
    }
};

class SolutionGCD
{
public:
    int getGCD(int a, int b)
    {
        int tmp = a % b;
        while (tmp != 0)
        {
            a = b;
            b = tmp;
            tmp = a % b;
        }

        return b;
    }

    ListNode *insertGreatestCommonDivisors(ListNode *head)
    {
        ListNode *p = head;

        while (p->next)
        {
            int gcd = getGCD(p->val, p->next->val);
            ListNode *mid = new ListNode(gcd);
            mid->next = p->next;
            p->next = mid;
            p = p->next->next;
        }

        return head;
    }
};

class Solution
{
public:
    int getGCD(int a, int b)
    {
        int tmp = a % b;
        while (tmp != 0)
        {
            a = b;
            b = tmp;
            tmp = a % b;
        }

        return b;
    }

    ListNode *insertGreatestCommonDivisors(ListNode *head)
    {
        ListNode *p = head;

        while (p->next)
        {
            int gcd = getGCD(p->val, p->next->val);
            ListNode *mid = new ListNode(gcd);
            mid->next = p->next;
            p->next = mid;
            p = p->next->next;
        }

        return head;
    }
};

int main()
{
    vector<vector<int>> heads = {
        {18, 6, 10, 3}, // 18,6,6,2,10,1,3
        {7},            // 7
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    ListNode *head = array2list(heads[group]);

    Solution s;
    ListNode *result = s.insertGreatestCommonDivisors(head);
    output(result);

    return 0;
}
