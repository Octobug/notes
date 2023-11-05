#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    string makeSmallestPalindrome(string s)
    {
        int left = 0, right = s.size() - 1;

        while (left < right)
        {
            if (s[left] > s[right])
                s[left] = s[right];
            else if (s[left] < s[right])
                s[right] = s[left];

            left++;
            right--;
        }

        return s;
    }
};

int main()
{
    vector<string> ss = {
        "egcfe", // efcfe
        "abcd",  // abba
        "seven", // neven
    };

    int group;
    cout << "Please enter group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.makeSmallestPalindrome(ss[group]) << endl;

    return 0;
}
