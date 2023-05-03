#include <iostream>

using namespace std;

class MyLinkedList
{
public:
    MyLinkedList()
    {
        this->val = -1;
        this->next = nullptr;
    }

    int get(int index)
    {
        MyLinkedList *p = this;
        for (int i = 0; i <= index; i++)
        {
            if (p->next)
            {
                p = p->next;
            }
            else
            {
                return -1;
            }
        }
        return p->val;
    }

    void addAtHead(int val)
    {
        MyLinkedList *node = new MyLinkedList();
        node->val = val;
        node->next = this->next;
        this->next = node;
    }

    void addAtTail(int val)
    {
        MyLinkedList *node = new MyLinkedList();
        node->val = val;

        MyLinkedList *p = this;
        while (p->next)
        {
            p = p->next;
        }
        p->next = node;
    }

    void addAtIndex(int index, int val)
    {
        MyLinkedList *node = new MyLinkedList();
        node->val = val;

        MyLinkedList *p = this;
        MyLinkedList *pre;

        while (p && index >= 0)
        {
            pre = p;
            p = p->next;
            index--;
        }

        if (index < 0)
        {
            node->next = p;
            pre->next = node;
        }
    }

    void deleteAtIndex(int index)
    {
        MyLinkedList *p = this;
        MyLinkedList *pre;

        for (int i = 0; i <= index; i++)
        {
            if (p->next)
            {
                pre = p;
                p = p->next;
            }
            else
            {
                return;
            }
        }
        MyLinkedList *tmp = p;
        pre->next = p->next;
        delete tmp;
    }

    int val;
    MyLinkedList *next;
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */

int main()
{
    MyLinkedList *myLinkedList = new MyLinkedList();
    myLinkedList->addAtHead(1);
    myLinkedList->addAtTail(3);
    myLinkedList->addAtIndex(1, 2);       // linked list becomes 1->2->3
    cout << myLinkedList->get(1) << endl; // return 2
    myLinkedList->deleteAtIndex(1);       // now the linked list is 1->3
    cout << myLinkedList->get(1) << endl; // return 3
    return 0;
}
