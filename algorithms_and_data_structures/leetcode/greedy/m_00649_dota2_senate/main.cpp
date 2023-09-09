#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution
{
public:
    string predictPartyVictory(string senate)
    {
        string d = "Dire", r = "Radiant";

        if (senate.size() == 1)
        {
            if (senate[0] == r[0])
                return r;
            else
                return d;
        }

        queue<char> que;
        int dcount = 0, rcount = 0;

        for (int i = 0; i < senate.size(); i++)
        {
            que.push(senate[i]);
            if (senate[i] == d[0])
                dcount++;
            else
                rcount++;
        }

        char c;
        int flag = 0;
        while (dcount > 0 && rcount > 0)
        {
            c = que.front();
            que.pop();

            if (c == 'D')
            {
                if (flag < 0)
                    dcount--;
                else
                    que.push(c);

                flag++;
            }
            else
            {
                if (flag > 0)
                    rcount--;
                else
                    que.push(c);

                flag--;
            }
        }

        if (dcount == 0)
            return r;
        else
            return d;
    }
};

class SolutionO2
{
public:
    string predictPartyVictory(string senate)
    {
        string d = "Dire", r = "Radiant";
        bool DExist = true, RExist = true;
        int flag = 0;

        while (DExist && RExist)
        {
            DExist = false;
            RExist = false;

            for (int i = 0; i < senate.size(); i++)
            {
                if (senate[i] == 'D')
                {
                    if (flag < 0)
                        senate[i] = '0';
                    else
                        DExist = true;
                    flag++;
                }
                else if (senate[i] == 'R')
                {
                    if (flag > 0)
                        senate[i] = '0';
                    else
                        RExist = true;
                    flag--;
                }
            }
        }

        return DExist ? d : r;
    }
};

int main()
{
    vector<string> senates = {
        "RD",               // Radiant
        "RDD",              // Dire
        "DDRRR",            // Dire
        "DRRDRDRDRDDRDRDR", // Radiant
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.predictPartyVictory(senates[group]) << endl;

    return 0;
}
