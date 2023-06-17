#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
    vector<string> result;
    vector<int> address;

public:
    void backtrack(string &s, int begin, int limit)
    {
        if (limit == 0)
        {
            if (address.size() == 4)
            {
                string ip = to_string(address[0]);
                for (int i = 1; i < 4; i++)
                    ip += ("." + to_string(address[i]));

                result.push_back(ip);
            }
            return;
        }

        int leftSize = s.size() - begin;
        int len = limit == 1 ? leftSize : 1;
        int lenLimit = min(3, leftSize);
        for (; len <= lenLimit; len++)
        {
            if (leftSize < limit || leftSize / limit > 3)
                continue;

            if (len > 1 && s[begin] == '0')
                continue;
            string part = s.substr(begin, len);
            int partInt = stoi(part);
            if (partInt >= 0 && partInt <= 255)
                address.push_back(partInt);
            else
                continue;

            backtrack(s, begin + len, limit - 1);

            address.pop_back();
        }
    }

    vector<string> restoreIpAddresses(string s)
    {
        backtrack(s, 0, 4);
        return result;
    }
};

int main()
{
    vector<string> inputs = {
        "25525511135",
        "0000",
        "101023",
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<string> result = s.restoreIpAddresses(inputs[group]);
    output(result);

    return 0;
}
