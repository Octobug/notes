#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int countGoodTriplets(vector<int> &arr, int a, int b, int c)
    {
        int result = 0;

        for (int i = 0; i < arr.size(); i++)
        {
            for (int j = i + 1; j < arr.size(); j++)
            {
                for (int k = j + 1; k < arr.size(); k++)
                {
                    if (abs(arr[i] - arr[j]) <= a &&
                        abs(arr[j] - arr[k]) <= b &&
                        abs(arr[i] - arr[k]) <= c)
                        result++;
                }
            }
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> arrs = {
        {3, 0, 1, 1, 9, 7}, // 4
        {1, 1, 2, 2, 3},    // 0
    };
    vector<int> as = {7, 0};
    vector<int> bs = {2, 0};
    vector<int> cs = {3, 1};

    int group;
    cout << "Please enter group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.countGoodTriplets(
                arrs[group], as[group], bs[group], cs[group])
         << endl;

    return 0;
}
