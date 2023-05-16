#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    string reverseLeftWords(string s, int n)
    {
        int left = 0, right = n - 1;
        this->reverse(s, left, right);

        left = n, right = s.size() - 1;
        this->reverse(s, left, right);

        left = 0, right = s.size() - 1;
        this->reverse(s, left, right);

        return s;
    }

    void reverse(string &s, int left, int right)
    {
        while (left < right)
        {
            swap(s[left++], s[right--]);
        }
    }
};

int main()
{
    vector<string> groups = {
        "abcdefg",
        "lrloseumgh",
        "yvjfhebhdvgqhlddkadceojazrxegpolllrthcjlbovbhlagkoumnotecmogwfcfkxiokiyanknvbywihhfgprvqdwpdmvjbhbdd",
    };

    int group;
    cout << "Please input group: ";
    cin >> group;

    int n;
    cout << "Please input k: ";
    cin >> n;

    Solution s;
    string result = s.reverseLeftWords(groups[group - 1], n);
    cout << result << endl;

    return 0;
}
