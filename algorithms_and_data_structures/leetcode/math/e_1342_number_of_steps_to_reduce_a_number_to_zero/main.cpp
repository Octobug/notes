#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution1
{
public:
    int steps = 0;
    int initLen = 64;
    int tmp = 0;
    vector<int> store = vector<int>(initLen, 0);

    int numberOfSteps(int num)
    {
        // pre calculate
        if (!store[initLen - 1])
        {
            store[0] = 0;
            store[1] = 1;

            for (int i = 2; i < initLen; i++)
            {
                steps = 0;
                tmp = i;
                while (tmp)
                {
                    if (store[tmp])
                    {
                        steps += store[tmp];
                        store[i] = steps;
                        break;
                    }
                    else
                    {
                        steps++;
                    }

                    if (i % 2 == 0)
                    {
                        tmp /= 2;
                    }
                    else
                    {
                        tmp--;
                    }
                }
            }
        }

        steps = 0;
        while (num)
        {
            if (num < initLen)
            {
                steps += store[num];
                break;
            }
            else
            {
                steps++;
            }

            if (num % 2 == 0)
            {
                num /= 2;
            }
            else
            {
                num--;
            }
        }
        return steps;
    }
};

class Solution2
{
public:
    int numberOfSteps(int num)
    {
        int steps = 0;
        while (num)
        {
            if (num % 2)
            {
                num--;
            }
            else
            {
                num /= 2;
            }
            steps++;
        }
        return steps;
    }
};

int main()
{
    Solution1 s1;
    Solution1 s2;

    int num = 14;
    int ans = s1.numberOfSteps(num);
    cout << ans << endl;
    ans = s2.numberOfSteps(num);
    cout << ans << endl;

    num = 8;
    ans = s1.numberOfSteps(num);
    cout << ans << endl;
    ans = s2.numberOfSteps(num);
    cout << ans << endl;

    num = 123;
    ans = s1.numberOfSteps(num);
    cout << ans << endl;
    ans = s2.numberOfSteps(num);
    cout << ans << endl;
}
