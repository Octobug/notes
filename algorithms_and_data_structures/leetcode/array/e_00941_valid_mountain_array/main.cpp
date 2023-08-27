#include <iostream>
#include <vector>

using namespace std;

class SolutionTraverse
{
public:
    bool validMountainArray(vector<int> &arr)
    {
        if (arr.size() < 3)
            return false;

        int up = false;
        int down = false;
        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i] == arr[i - 1])
                return false;

            if (arr[i] > arr[i - 1])
            {
                if (down)
                    return false;
                up = true;
            }
            else
            {
                if (!up)
                    return false;
                down = true;
            }
        }

        return up && down;
    }
};

class Solution
{
public:
    bool validMountainArray(vector<int> &arr)
    {
        if (arr.size() < 3)
            return false;

        int left = 0, right = arr.size() - 1;

        while (left < arr.size() - 1 && arr[left] < arr[left + 1])
            left++;

        while (right > 0 && arr[right] < arr[right - 1])
            right--;

        if (left == arr.size() - 1 || right == 0)
            return false;

        return left == right;
    }
};

int main()
{
    vector<vector<int>> arrs = {
        {2, 1},                         // 0
        {3, 5, 5},                      // 0
        {0, 3, 2, 1},                   // 1
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, // 0
        {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, // 0
        {2, 0, 2},                      // 0
        {0, 1, 2, 1, 2},                // 0
    };
    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    Solution s;
    cout << s.validMountainArray(arrs[group]) << endl;

    return 0;
}
