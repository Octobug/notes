#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution
{
public:
    int trap(vector<int> &height)
    {
        int result = 0;
        int maxIdx = 0;
        int tmpIdx;
        for (int i = 1; i < height.size(); i++)
        {
            if (height[i] >= height[maxIdx])
            {
                tmpIdx = maxIdx + 1;
                while (tmpIdx < i)
                {
                    result += (height[maxIdx] - height[tmpIdx]);
                    tmpIdx++;
                }
                maxIdx = i;
            }
        }

        maxIdx = height.size() - 1;
        for (int i = height.size() - 2; i >= 0; i--)
        {
            if (height[i] > height[maxIdx])
            {
                tmpIdx = maxIdx - 1;
                while (tmpIdx > i)
                {
                    result += (height[maxIdx] - height[tmpIdx]);
                    tmpIdx--;
                }
                maxIdx = i;
            }
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> heights = {
        {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}, // 6
        {4, 2, 0, 3, 2, 5},                   // 9
        {2, 0, 2},                            // 2
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.trap(heights[group]) << endl;

    return 0;
}
