#include <iostream>
#include <stack>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> nextGreaterElements(vector<int> &nums)
    {
        vector<int> result(nums.size(), -1);

        stack<int> st;
        st.push(0);

        for (int i = 1; i < nums.size(); i++)
        {
            while (!st.empty() && nums[i] > nums[st.top()])
            {
                result[st.top()] = nums[i];
                st.pop();
            }
            st.push(i);
        }

        for (int i = 0; i < nums.size(); i++)
        {
            while (!st.empty() && nums[i] > nums[st.top()])
            {
                if (result[st.top()] == -1)
                    result[st.top()] = nums[i];
                st.pop();
            }

            st.push(i);
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> nums = {
        {1, 2, 1},       // 2,-1,2
        {1, 2, 3, 4, 3}, // 2,3,4,-1,4
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<int> result = s.nextGreaterElements(nums[group]);
    output(result);

    return 0;
}
