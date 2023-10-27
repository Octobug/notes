#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>> &image)
    {
        int row = image.size();
        int col = image[0].size();
        for (int i = 0; i < row; i++)
        {
            int left = 0, right = col - 1;
            while (left < right)
                swap(image[i][left++], image[i][right--]);

            for (int j = 0; j < col; j++)
                image[i][j] ^= 1;
        }

        return image;
    }
};

int main()
{
    vector<vector<vector<int>>> images = {
        {
            {1, 1, 0},
            {1, 0, 1},
            {0, 0, 0},
        }, // [[1,0,0],[0,1,0],[1,1,1]]
        {
            {1, 1, 0, 0},
            {1, 0, 0, 1},
            {0, 1, 1, 1},
            {1, 0, 1, 0},
        }, // [[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]
    };

    int group;
    cout << "Please enter group: ";
    cin >> group;
    group--;

    Solution s;
    vector<vector<int>> result = s.flipAndInvertImage(images[group]);
    output2d(result);

    return 0;
}
