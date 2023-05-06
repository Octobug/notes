#include <iostream>
#include <vector>
#include "linkedlist.h"

using namespace std;

class Solution
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

int main()
{
    vector<int> list1 = {1, 2, 3, 4, 5};
    vector<int> list2 = {1};
    vector<int> list3 = {1, 2};
    vector<vector<int>> groups = {list1, list2, list3};

    int group;
    cout << "Please input group: ";
    cin >> group;

    int n;
    cout << "Please input n: ";
    cin >> n;

    ListNode *head = array2list(groups[group - 1]);

    Solution s;
    ListNode *result = s.removeNthFromEnd(head, n);

    output(result);

    return 0;
}
