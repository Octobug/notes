#include <iostream>
#include <vector>
#include "linkedlist.h"

using namespace std;

class Solution
{
public:
    int getDecimalValue(ListNode *head)
    {
        int result = 0;
        ListNode *p = head;

        while (p)
        {
            result = result * 2 + p->val;
            p = p->next;
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> heads = {
        {1, 0, 1}, // 5
        {0},       // 0
    };

    int group;
    cout << "Please enter group: ";
    cin >> group;
    group--;

    ListNode *head = array2list(heads[group]);

    Solution s;
    cout << s.getDecimalValue(head) << endl;

    return 0;
}
