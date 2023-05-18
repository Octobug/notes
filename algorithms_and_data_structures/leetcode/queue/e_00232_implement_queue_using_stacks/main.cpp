#include <iostream>
#include <stack>

using namespace std;

class MyQueue
{
public:
    stack<int> stackIn;
    stack<int> stackOut;
    MyQueue()
    {
    }

    void push(int x)
    {
        this->stackIn.push(x);
    }

    int pop()
    {
        int result;
        if (this->stackOut.empty())
        {
            while (this->stackIn.size() > 1)
            {
                this->stackOut.push(this->stackIn.top());
                this->stackIn.pop();
            }

            result = this->stackIn.top();
            this->stackIn.pop();
            return result;
        }
        else
        {
            result = this->stackOut.top();
            this->stackOut.pop();
            return result;
        }
    }

    int peek()
    {
        if (this->stackOut.empty())
        {
            while (!(this->stackIn.empty()))
            {
                this->stackOut.push(this->stackIn.top());
                this->stackIn.pop();
            }
        }
        return stackOut.top();
    }

    bool empty()
    {
        return this->stackIn.empty() && this->stackOut.empty();
    }
};

int main()
{
    MyQueue *que1 = new MyQueue();
    que1->push(1);
    que1->push(2);
    cout << que1->peek() << endl;
    cout << que1->pop() << endl;
    cout << que1->empty() << endl;

    MyQueue *que2 = new MyQueue();
    que2->push(1);
    cout << que2->pop() << endl;
    cout << que2->empty() << endl;

    return 0;
}
