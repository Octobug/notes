#include <iostream>
#include <vector>
#include "input.h"

using namespace std;

class Solution
{
public:
    int wateringPlants(vector<int> &plants, int capacity)
    {
        int left = capacity;
        int result = 0;

        for (int i = 0; i < plants.size(); i++)
        {
            if (left < plants[i])
            {
                result += 2 * i;
                left = capacity;
            }

            result++;
            left = left - plants[i];
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> plants = {
        {2, 2, 3, 3},          // 14
        {1, 1, 1, 4, 2, 3},    // 30
        {7, 7, 7, 7, 7, 7, 7}, // 49
    };

    vector<int> capacities = {5, 4, 8};

    int group = getGroup();
    Solution s;
    cout << s.wateringPlants(plants[group], capacities[group]) << endl;

    return 0;
}
