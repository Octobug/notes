#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    vector<int> decode(vector<int> &encoded, int first)
    {
        vector<int> res(encoded.size() + 1);
        res[0] = first;
        for (int i = 1; i < res.size(); i++)
        {
            res[i] = encoded[i - 1] ^ res[i - 1];
        }
        return res;
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

    vector<int> encoded = {1, 2, 3};
    int first = 1;
    vector<int> res = s.decode(encoded, first);
    output(res);

    encoded = {6, 2, 7, 3};
    first = 4;
    res = s.decode(encoded, first);
    output(res);
}
