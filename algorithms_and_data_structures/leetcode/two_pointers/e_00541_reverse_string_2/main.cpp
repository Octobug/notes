#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    string reverseStr(string s, int k)
    {
        int round = s.size() / k + 1;
        for (int i = 0; i < round; i += 2)
        {
            int left = i * k;
            int len = k;
            if (left + len > s.size())
            {
                len = s.size() - left;
            }
            int right = left + len - 1;

            while (left < right)
            {
                swap(s[left++], s[right--]);
            }
        }

        return s;
    }
};

int main()
{
    vector<string> groups = {
        "abcdefg",
        "abcd",
        "abcdefg",
        "hyzqyljrnigxvdtneasepfahmtyhlohwxmkqcdfehybknvdmfrfvtbsovjbdhevlfxpdaovjgunjqlimjkfnqcqnajmebeddqsgl",
    };

    int group;
    int k;

    cout << "Please input group: ";
    cin >> group;

    cout << "Please input k: ";
    cin >> k;

    Solution s;
    string result = s.reverseStr(groups[group - 1], k);

    cout << result << endl;

    return 0;
}
