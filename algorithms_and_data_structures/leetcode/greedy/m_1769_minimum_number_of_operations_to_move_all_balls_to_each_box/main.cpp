#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    vector<int> minOperations(string boxes)
    {
        vector<int> ans(boxes.length());
        vector<int> countLeft(boxes.length());
        int countBall = boxes[0] - '0';

        for (int i = 1; i < boxes.length(); i++)
        {
            countLeft[i] = boxes[i] - '0';
            if (countLeft[i])
            {
                countBall++;
                ans[0] += i;
            }
            countLeft[i] = countBall - countLeft[i];
        }

        for (int i = 1; i < boxes.length(); i++)
        {
            ans[i] = ans[i - 1] - (countBall - countLeft[i]) + countLeft[i];
        }

        return ans;
    }
};

void output(vector<int> &arr)
{
    cout << '[';
    for (int i = 0; i < arr.size(); ++i)
    {
        cout << arr[i];
        if (i != arr.size() - 1)
        {
            cout << ',';
        }
    }
    cout << ']' << endl;
}

int main()
{
    Solution s;

    string boxes1 = "110";
    vector<int> ans1 = s.minOperations(boxes1);
    output(ans1);

    string boxes2 = "001011";
    vector<int> ans2 = s.minOperations(boxes2);
    output(ans2);
}
