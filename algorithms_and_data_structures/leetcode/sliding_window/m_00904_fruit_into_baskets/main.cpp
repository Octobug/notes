#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int totalFruit(vector<int> &fruits)
    {
        int max_len = 1;
        int left = 0;
        int bsk_l = fruits[left];
        int bsk_r = -1;

        for (int right = 1; right < fruits.size(); right++)
        {
            int new_type = fruits[right];
            if (new_type != bsk_l && new_type != bsk_r)
            {
                if (bsk_r != -1)
                {
                    int back = right;
                    int pre_type = fruits[right - 1];
                    while (fruits[back] == new_type || fruits[back] == pre_type)
                    {
                        back--;
                    }
                    left = back + 1;
                }
                bsk_r = bsk_l;
                bsk_l = new_type;
            }
            int cur_len = right - left + 1;
            if (cur_len > max_len)
            {
                max_len = cur_len;
            }
        }

        return max_len;
    }
};

int main()
{
    vector<int> f1 = {1, 2, 1};
    vector<int> f2 = {0, 1, 2, 2};
    vector<int> f3 = {1, 2, 3, 2, 2};
    vector<int> f4 = {3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};
    vector<int> f5 = {1, 1, 6, 5, 6, 6, 1, 1, 1, 1};
    vector<int> f6 = {1, 0, 1, 4, 1, 4, 1, 2, 3};

    vector<vector<int>> groups = {f1, f2, f3, f4, f5, f6};

    int group;
    cout << "Please input group: ";
    cin >> group;

    Solution s;
    cout << s.totalFruit(groups[group - 1]) << endl;

    return 0;
}
