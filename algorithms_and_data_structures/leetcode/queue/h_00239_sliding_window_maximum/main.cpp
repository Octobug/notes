#include <iostream>
#include <deque>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
    class MonoQueue
    {
    public:
        deque<int> que;

        void pop()
        {
            if (!que.empty())
            {
                que.pop_front();
            }
        }

        void push(int value)
        {
            while (!que.empty() && value > que.back())
            {
                que.pop_back();
            }
            que.push_back(value);
        }

        int front()
        {
            return que.front();
        }
    };

public:
    vector<int>
    maxSlidingWindow(vector<int> &nums, int k)
    {
        vector<int> result;
        MonoQueue que;

        int left = 0, right = 0;
        while (right < k)
        {
            que.push(nums[right++]);
        }

        while (right < nums.size())
        {
            result.push_back(que.front());
            if (nums[left++] >= que.front())
            {
                que.pop();
            }
            que.push(nums[right++]);
        }

        result.push_back(que.front());

        return result;
    }
};

int main()
{
    vector<vector<int>> groups = {
        {1, 3, -1, -3, 5, 3, 6, 7},
        {1},
        {1, 3, 1, 2, 0, 5},
    };
    int group, k;
    cout << "Please input group: ";
    cin >> group;
    cout << "Please input k: ";
    cin >> k;
    Solution s;
    vector<int> result = s.maxSlidingWindow(groups[group - 1], k);
    output(result);

    return 0;
}
