#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int minMovesToSeat(vector<int> &seats, vector<int> &students)
    {
        sort(seats.begin(), seats.end());
        sort(students.begin(), students.end());

        int result = 0;

        for (int i = 0; i < seats.size(); i++)
            result += abs(seats[i] - students[i]);

        return result;
    }
};

int main()
{
    vector<vector<int>> seats = {
        {3, 1, 5},    // 4
        {4, 1, 5, 9}, // 7
        {2, 2, 6, 6}, // 4
    };
    vector<vector<int>> students = {
        {2, 7, 4},
        {1, 3, 2, 6},
        {1, 3, 2, 6},
    };

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.minMovesToSeat(seats[group], students[group]) << endl;

    return 0;
}
