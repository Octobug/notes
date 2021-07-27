#include <iostream>
#include <vector>
#include <string>

using namespace std;

class SubrectangleQueries
{
public:
    vector<vector<int>> rec;

    SubrectangleQueries(vector<vector<int>> &rectangle)
    {
        rec = rectangle;
    }

    void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue)
    {
        for (int i = row1; i <= row2; i++)
        {
            for (int j = col1; j <= col2; j++)
            {
                rec[i][j] = newValue;
            }
        }
    }

    int getValue(int row, int col)
    {
        return rec[row][col];
    }
};

/**
 * Your SubrectangleQueries object will be instantiated and called as such:
 * SubrectangleQueries* obj = new SubrectangleQueries(rectangle);
 * obj->updateSubrectangle(row1,col1,row2,col2,newValue);
 * int param_2 = obj->getValue(row,col);
 */

void output(vector<vector<int>> &rec)
{
    for (int i = 0; i < rec.size(); i++)
    {
        vector<int> rows = rec[i];
        for (int j = 0; j < rows.size(); j++)
        {
            printf("%4d", rows[j]);
        }
        cout << endl;
    }
}

int main()
{
    vector<vector<int>> rec1 = {{1, 2, 1}, {4, 3, 4}, {3, 2, 1}, {1, 1, 1}};
    SubrectangleQueries *sq1 = new SubrectangleQueries(rec1);
    output(sq1->rec);
    int res1 = sq1->getValue(0, 2);
    cout << res1 << endl;

    sq1->updateSubrectangle(0, 0, 3, 2, 5);
    output(sq1->rec);
    res1 = sq1->getValue(0, 2);
    cout << res1 << endl;
    res1 = sq1->getValue(3, 1);
    cout << res1 << endl;

    sq1->updateSubrectangle(3, 0, 3, 2, 10);
    output(sq1->rec);
    res1 = sq1->getValue(3, 1);
    cout << res1 << endl;
    res1 = sq1->getValue(0, 2);
    cout << res1 << endl;

    vector<vector<int>> rec2 = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    SubrectangleQueries *sq2 = new SubrectangleQueries(rec2);
    output(sq2->rec);
    int res2 = sq2->getValue(0, 0);
    cout << res2 << endl;

    sq2->updateSubrectangle(0, 0, 2, 2, 100);
    output(sq2->rec);
    res2 = sq2->getValue(0, 0);
    cout << res2 << endl;
    res2 = sq2->getValue(2, 2);
    cout << res2 << endl;

    sq2->updateSubrectangle(1, 1, 2, 2, 20);
    output(sq2->rec);
    res2 = sq2->getValue(2, 2);
    cout << res2 << endl;
}
