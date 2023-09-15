#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    void reverseString(vector<char> &s)
    {
        int left = 0;
        int right = s.size() - 1;
        while (left < right)
            swap(s[left++], s[right--]);
    }
};

int main()
{
    vector<vector<char>> groups = {
        {'h', 'e', 'l', 'l', 'o'},
        {'H', 'a', 'n', 'n', 'a', 'h'},
    };
    int group;

    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    s.reverseString(groups[group]);
    output(groups[group]);

    return 0;
}
