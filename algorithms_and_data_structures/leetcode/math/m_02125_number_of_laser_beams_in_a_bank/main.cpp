#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int numberOfBeams(vector<string> &bank)
    {
        int lastBeams = 0, currBeams = 0, result = 0;
        int row = bank.size(), col = bank[0].size();

        for (int i = 0; i < row; i++)
        {
            currBeams = 0;
            for (int j = 0; j < col; j++)
                currBeams += (bank[i][j] == '1' ? 1 : 0);

            if (currBeams > 0)
            {
                result += currBeams * lastBeams;
                lastBeams = currBeams;
            }
        }

        return result;
    }
};

int main()
{
    vector<vector<string>> banks = {
        {"011001", "000000", "010100", "001000"}, // 8
        {"000", "111", "000"},                    // 0
    };

    int group;
    cout << "Please enter group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.numberOfBeams(banks[group]) << endl;

    return 0;
}
