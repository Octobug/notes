#include <iostream>

using namespace std;

class Solution
{
public:
    int sum(int num1, int num2)
    {
        return num1 + num2;
    }
};

int main()
{
    int num1, num2;

    cout << "Please input num1: ";
    cin >> num1;

    cout << "Please input num2: ";
    cin >> num2;

    Solution s;
    cout << s.sum(num1, num2) << endl;

    return 0;
}
