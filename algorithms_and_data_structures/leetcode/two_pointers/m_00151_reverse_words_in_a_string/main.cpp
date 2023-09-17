#include <iostream>
#include <vector>

using namespace std;

class SolutionSlow
{
public:
    string reverseWords(string s)
    {
        int cur = 0;
        while (s[cur] == ' ')
            cur++;
        int start = cur;

        while (cur < s.size() && s[cur] != ' ')
            cur++;

        string result = s.substr(start, cur - start);

        while (cur < s.size())
        {
            while (cur < s.size() && s[cur] == ' ')
                cur++;
            start = cur;

            while (cur < s.size() && s[cur] != ' ')
                cur++;

            if (start < s.size())
                result = s.substr(start, cur - start) + " " + result;
        }

        return result;
    }
};

class Solution
{
public:
    string reverseWords(string s)
    {
        int left = 0;
        int right = s.size() - 1;

        while (left < right)
        {
            swap(s[left], s[right]);
            left++;
            right--;
        }

        int base = 0;
        int begin = 0;
        int end = 0;
        int cur = 0;
        int len = 0;
        int shift = 0;

        while (cur < s.size())
        {
            while (cur < s.size() && s[cur] == ' ')
                cur++;
            if (cur >= s.size())
                break;
            begin = cur;

            while (cur < s.size() && s[cur] != ' ')
                cur++;
            end = cur - 1;
            len = end - begin + 1;
            shift = begin - base;

            while (end >= begin)
                swap(s[begin++], s[end--]);

            for (int i = 0; i < len; i++)
                s[base + i] = s[base + i + shift];
            base += len;
            s[base++] = ' ';
        }

        s.resize(base - 1);

        return s;
    }
};

int main()
{
    vector<string> groups = {
        "the sky is blue",
        "  hello world  ",
        "a good   example",
        "EPY2giL",
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.reverseWords(groups[group]) << endl;

    return 0;
}
