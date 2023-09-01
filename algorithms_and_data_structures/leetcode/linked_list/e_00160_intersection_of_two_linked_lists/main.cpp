#include <iostream>
#include <vector>
#include "linkedlist.h"

using namespace std;

class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        int lenA = 0, lenB = 0;
        ListNode *pa = headA, *pb = headB;

        while (pa)
        {
            lenA++;
            pa = pa->next;
        }

        while (pb)
        {
            lenB++;
            pb = pb->next;
        }

        pa = headA;
        pb = headB;

        if (lenB > lenA)
        {
            swap(lenA, lenB);
            swap(pa, pb);
        }

        int diff = lenA - lenB;
        while (diff--)
            pa = pa->next;

        while (pa)
        {
            if (pa == pb)
                return pa;

            pa = pa->next;
            pb = pb->next;
        }

        return nullptr;
    }
};

int main()
{
    vector<int> a1 = {4, 1};
    vector<int> b1 = {5, 6, 1};
    vector<int> c1 = {8, 4, 5};

    vector<int> a2 = {1, 9, 1};
    vector<int> b2 = {3};
    vector<int> c2 = {2, 4};

    vector<int> a3 = {2, 6, 4};
    vector<int> b3 = {1, 5};
    vector<int> c3 = {};

    vector<vector<int>> listAs = {a1, a2, a3};
    vector<vector<int>> listBs = {b1, b2, b3};
    vector<vector<int>> listCs = {c1, c2, c3};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    ListNode *listA = array2list(listAs[group]);
    ListNode *listB = array2list(listBs[group]);
    ListNode *listC = array2list(listCs[group]);

    ListNode *pa = listA;
    while (pa->next)
        pa = pa->next;
    pa->next = listC;

    ListNode *pb = listB;
    while (pb->next)
        pb = pb->next;
    pb->next = listC;

    Solution s;
    ListNode *intersect = s.getIntersectionNode(listA, listB);
    output(intersect);

    return 0;
}
