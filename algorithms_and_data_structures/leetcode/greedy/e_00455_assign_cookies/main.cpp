#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int count = 0;
        for (int gi = 0, si = 0; gi < g.size() && si < s.size(); si++)
        {
            if (g[gi] <= s[si])
            {
                gi++;
                count++;
            }
        }

        return count;
    }
};

int main()
{
    vector<vector<vector<int>>> inputs = {
        {{1, 2, 3}, {1, 1}},
        {{1, 2}, {1, 2, 3}},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.findContentChildren(inputs[group][0], inputs[group][1]) << endl;

    return 0;
}
