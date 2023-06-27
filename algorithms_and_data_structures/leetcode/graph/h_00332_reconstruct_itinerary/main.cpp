#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<string> result;
    unordered_map<string, map<string, int>> graph;

    bool backtrack(int ticketAmount)
    {
        if (result.size() == ticketAmount + 1)
            return true;

        for (pair<const string, int> &dest : graph[result[result.size() - 1]])
        {
            if (dest.second > 0)
            {
                result.push_back(dest.first);
                dest.second--;

                if (backtrack(ticketAmount))
                    return true;

                result.pop_back();
                dest.second++;
            }
        }

        return false;
    }

    vector<string> findItinerary(vector<vector<string>> &tickets)
    {
        for (const vector<string> &vec : tickets)
            graph[vec[0]][vec[1]]++;

        result.push_back("JFK");
        backtrack(tickets.size());
        return result;
    }
};

int main()
{
    vector<vector<vector<string>>> inputs = {
        {{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}},
        {{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}},
        {{"JFK", "KUL"}, {"JFK", "NRT"}, {"NRT", "JFK"}},
        {{"EZE", "TIA"}, {"EZE", "HBA"}, {"AXA", "TIA"}, {"JFK", "AXA"}, {"ANU", "JFK"}, {"ADL", "ANU"}, {"TIA", "AUA"}, {"ANU", "AUA"}, {"ADL", "EZE"}, {"ADL", "EZE"}, {"EZE", "ADL"}, {"AXA", "EZE"}, {"AUA", "AXA"}, {"JFK", "AXA"}, {"AXA", "AUA"}, {"AUA", "ADL"}, {"ANU", "EZE"}, {"TIA", "ADL"}, {"EZE", "ANU"}, {"AUA", "ANU"}},
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    vector<string> result = s.findItinerary(inputs[group]);
    output(result);

    return 0;
}
