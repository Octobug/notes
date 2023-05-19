#include <iostream>
#include <queue>

using namespace std;

class MyStack
{
public:
    queue<int> myQueue;

    MyStack()
    {
    }

    void push(int x)
    {
        myQueue.push(x);
    }

    int pop()
    {
        int queSize = myQueue.size();
        for (int i = 1; i < queSize; i++)
        {
            myQueue.push(myQueue.front());
            myQueue.pop();
        }
        int result = myQueue.front();
        myQueue.pop();
        return result;
    }

    int top()
    {
        int result = this->pop();
        myQueue.push(result);
        return result;
    }

    bool empty()
    {
        return myQueue.empty();
    }
};

int main()
{

    MyStack *myStack = new MyStack();
    myStack->push(1);
    myStack->push(2);
    cout << myStack->top() << endl;
    cout << myStack->pop() << endl;
    cout << myStack->empty() << endl;

    return 0;
}
