#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    int countMatches(vector<vector<string>> &items, string ruleKey, string ruleValue)
    {
        int typeIndex = 0;
        if (ruleKey == "color")
            typeIndex = 1;
        else if (ruleKey == "name")
            typeIndex = 2;

        int result = 0;

        for (int i = 0; i < items.size(); i++)
            if (items[i][typeIndex] == ruleValue)
                result++;

        return result;
    }
};

int main()
{
    vector<vector<vector<string>>> items = {
        {
            {"phone", "blue", "pixel"},
            {"computer", "silver", "lenovo"},
            {"phone", "gold", "iphone"},
        }, // 1
        {
            {"phone", "blue", "pixel"},
            {"computer", "silver", "phone"},
            {"phone", "gold", "iphone"},
        }, // 2
    };
    vector<string> ruleKeys = {"color", "type"};
    vector<string> ruleValues = {"silver", "phone"};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.countMatches(items[group], ruleKeys[group], ruleValues[group])
         << endl;

    return 0;
}
