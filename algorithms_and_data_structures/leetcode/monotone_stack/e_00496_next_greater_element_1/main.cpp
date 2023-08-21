#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2)
    {
        unordered_map<int, int> umap;
        for (int i = 0; i < nums1.size(); i++)
            umap[nums1[i]] = i;

        vector<int> result(nums1.size(), -1);

        stack<int> st;
        st.push(0);

        for (int i = 1; i < nums2.size(); i++)
        {
            while (!st.empty() && nums2[i] > nums2[st.top()])
            {
                if (umap.count(nums2[st.top()]))
                    result[umap[nums2[st.top()]]] = nums2[i];

                st.pop();
            }
            st.push(i);
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> nums1 = {
        {4, 1, 2}, // -1,3,-1
        {2, 4},    // 3,-1
    };

    vector<vector<int>> nums2 = {
        {1, 3, 4, 2},
        {1, 2, 3, 4},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<int> result = s.nextGreaterElement(nums1[group], nums2[group]);
    output(result);

    return 0;
}
