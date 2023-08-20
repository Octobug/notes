#include <iostream>
#include <stack>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> dailyTemperatures(vector<int> &temperatures)
    {
        stack<int> st;
        vector<int> result(temperatures.size(), 0);

        st.push(0);
        for (int i = 1; i < temperatures.size(); i++)
        {
            while (!st.empty() && temperatures[i] > temperatures[st.top()])
            {
                result[st.top()] = i - st.top();
                st.pop();
            }

            st.push(i);
        }
        return result;
    }
};

int main()
{
    vector<vector<int>> temps = {
        {73, 74, 75, 71, 69, 72, 76, 73}, // 1,1,4,2,1,1,0,0
        {30, 40, 50, 60},                 // 1,1,1,0
        {30, 60, 90},                     // 1,1,0
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<int> result = s.dailyTemperatures(temps[group]);
    output(result);

    return 0;
}
