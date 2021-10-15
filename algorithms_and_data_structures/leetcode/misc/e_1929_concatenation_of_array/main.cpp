#include <iostream>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

class Solution
{
public:
    vector<int> getConcatenation(vector<int> &nums)
    {
        vector<int> ans;
        ans.insert(ans.begin(), nums.begin(), nums.end());
        ans.insert(ans.begin() + nums.size(), nums.begin(), nums.end());
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
    vector<int> in1 = {1, 2, 1};
    vector<int> in2 = {1, 3, 2, 1};
    vector<int> res1 = s.getConcatenation(in1);
    vector<int> res2 = s.getConcatenation(in2);
    output(res1);
    output(res2);
}
