#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool isLongPressedName(string name, string typed)
    {
        int in = 0, it = 0, lenn = name.size(), lent = typed.size();

        if (lenn > lent)
            return false;

        while (in < lenn && it < lent)
        {
            if (name[in] != typed[it])
                return false;

            while (in < lenn && it < lent && name[in] == typed[it])
            {
                in++;
                it++;
            }

            while (it < lent && typed[it] == typed[it - 1])
                it++;
        }

        if (in < lenn || it < lent)
            return false;

        return true;
    }
};

int main()
{
    vector<string> names = {
        "alex",   // true
        "saeed",  // false
        "laiden", // true
        "alex",   // false
        "alexd",  // false
    };
    vector<string> typeds = {
        "aaleex",
        "ssaaedd",
        "laiden",
        "aaleexa",
        "ale",
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.isLongPressedName(names[group], typeds[group]) << endl;

    return 0;
}
