#include <iostream>
#include <stack>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        int result = 0;
        stack<int> st;
        heights.insert(heights.begin(), 0);
        heights.push_back(0);
        st.push(0);

        for (int i = 1; i < heights.size(); i++)
        {
            while (heights[i] < heights[st.top()])
            {
                int mid = st.top();
                st.pop();

                int left = st.top();
                int right = i;
                int w = right - left - 1;
                int h = heights[mid];
                result = max(result, w * h);
            }
            st.push(i);
        }
        return result;
    }
};

int main()
{
    vector<vector<int>> heights = {
        {2, 1, 5, 6, 2, 3}, // 10
        {2, 4},             // 4
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.largestRectangleArea(heights[group]) << endl;

    return 0;
}
