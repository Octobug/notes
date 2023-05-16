#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int strStr(string haystack, string needle)
    {
        vector<int> next = this->genNext(needle);

        int i = 0, j = 0;
        int haySize = haystack.size();
        int neeSize = needle.size();
        while (i < haySize && j < neeSize)
        {
            if (j == -1 || haystack[i] == needle[j])
            {
                i++;
                j++;
            }
            else
            {
                j = next[j];
            }
        }

        int result;
        if (j >= needle.size())
        {
            return i - needle.size();
        }
        else
        {
            return -1;
        }
    }

    vector<int> genNext(string &T)
    {
        vector<int> next(T.size(), 0);

        int i = 1, j = 0;
        next[j] = -1;
        while (i < T.size() - 1)
        {
            if (j == -1 || T[i] == T[j])
            {
                // 自我比较的过程中，相等时继续往右匹配，next[i] 保存匹配时的部分匹配值
                i++;
                j++;
                next[i] = j;
            }
            else
            {
                // 不匹配时，j 按部分匹配值回溯
                j = next[j];
            }
        }
        return next;
    }
};

int main()
{
    vector<vector<string>> groups = {
        {
            "sadbutsad",
            "leetcode",
            "ababcabcacbab",
            "hello",
        },
        {
            "sad",
            "leeto",
            "abcac",
            "ll",
        },
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.strStr(groups[0][group], groups[1][group]) << endl;

    return 0;
}
