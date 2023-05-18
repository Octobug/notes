#include <iostream>
#include <stack>

using namespace std;

class MyQueue
{
public:
    stack<int> orderStack;
    stack<int> reverseStack;
    MyQueue()
    {
    }

    void push(int x)
    {
        this->orderStack.push(x);
    }

    int pop()
    {
        int result;
        if (this->reverseStack.empty())
        {
            while (this->orderStack.size() > 1)
            {
                this->reverseStack.push(this->orderStack.top());
                this->orderStack.pop();
            }

            result = this->orderStack.top();
            this->orderStack.pop();
            return result;
        }
        else
        {
            result = this->reverseStack.top();
            this->reverseStack.pop();
            return result;
        }
    }

    int peek()
    {
        if (this->reverseStack.empty())
        {
            while (!(this->orderStack.empty()))
            {
                this->reverseStack.push(this->orderStack.top());
                this->orderStack.pop();
            }
        }
        return reverseStack.top();
    }

    bool empty()
    {
        return this->orderStack.empty() && this->reverseStack.empty();
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
