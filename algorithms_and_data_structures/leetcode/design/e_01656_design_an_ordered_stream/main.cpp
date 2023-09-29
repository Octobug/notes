#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class OrderedStream
{
public:
    vector<string> stm;
    int index = 0;

    OrderedStream(int n)
    {
        stm = vector<string>(n, "");
    }

    vector<string> insert(int idKey, string value)
    {
        idKey--;
        stm[idKey] = value;

        int oldIndex = index;
        while (index < stm.size() && stm[index] != "")
            index++;

        vector<string> sub(&stm[oldIndex], &stm[index]);

        return sub;
    }
};

int main()
{
    /**
     * Your OrderedStream object will be instantiated and called as such:
     * OrderedStream* obj = new OrderedStream(n);
     * vector<string> param_1 = obj->insert(idKey,value);
     */
    vector<int> inits = {5, 9};
    vector<vector<pair<int, string>>> inserts = {
        {
            {3, "ccccc"}, // Inserts (3, "ccccc"), returns [].
            {1, "aaaaa"}, // Inserts (1, "aaaaa"), returns ["aaaaa"].
            {2, "bbbbb"}, // Inserts (2, "bbbbb"), returns ["bbbbb", "ccccc"].
            {5, "eeeee"}, // Inserts (5, "eeeee"), returns [].
            {4, "ddddd"}, // Inserts (4, "ddddd"), returns ["ddddd", "eeeee"].
        },
        {
            {9, "nghbm"},
            {7, "hgeob"},
            {6, "mwlrz"},
            {4, "oalee"},
            {2, "bouhq"},
            {1, "mnknb"},
            {5, "qkxbj"},
            {8, "iydkk"},
            {3, "oqdnf"},
        },
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    OrderedStream *os = new OrderedStream(inits[group]);

    vector<string> res;
    for (int i = 0; i < inits[group]; i++)
    {
        res = os->insert(inserts[group][i].first, inserts[group][i].second);
        output(res);
    }

    output(os->stm);

    // Concatentating all the chunks returned:
    // [] + ["aaaaa"] + ["bbbbb", "ccccc"] + [] + ["ddddd", "eeeee"] = ["aaaaa", "bbbbb", "ccccc", "ddddd", "eeeee"]

    return 0;
}
