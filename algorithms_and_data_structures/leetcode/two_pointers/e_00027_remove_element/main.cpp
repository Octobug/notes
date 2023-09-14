#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    int removeElement(vector<int> &nums, int val)
    {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right)
        {
            while (left <= right && val != nums[left])
                left++;
            while (right >= left && val == nums[right])
                right--;

            if (left < right)
                swap(nums[left], nums[right]);
        }

        return left;
    }
};

int main()
{
    Solution s;

    vector<vector<int>> nums = {
        {3, 2, 2, 3},             // 2
        {0, 1, 2, 2, 3, 0, 4, 2}, // 5
        {2},                      // 0
    };
    vector<int> vals = {3, 2, 2};

    int group;
    cout << "Please input group: ";
    cin >> group;
    group--;

    cout << s.removeElement(nums[group], vals[group]) << endl;
}
