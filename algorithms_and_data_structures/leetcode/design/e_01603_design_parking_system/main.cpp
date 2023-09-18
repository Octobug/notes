#include <iostream>
#include <vector>
#include <string>

using namespace std;

class ParkingSystem
{
public:
    int _big, _medium, _small;

    ParkingSystem(int big, int medium, int small)
    {
        _big = big;
        _medium = medium;
        _small = small;
    }

    bool addCar(int carType)
    {
        switch (carType)
        {
        case 1:
            if (_big)
            {
                return _big--;
            }
            return false;
        case 2:
            if (_medium)
            {
                return _medium--;
            }
            return false;
        case 3:
            if (_small)
            {
                return _small--;
            }
            return false;
        default:
            return false;
        }
    }
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */

void output(vector<bool> &arr)
{
    cout << '[';
    for (int i = 0; i < arr.size(); ++i)
    {
        cout << arr[i];
        if (i != arr.size() - 1)
        {
            cout << ',';
        }
    }
    cout << ']' << endl;
}

int main()
{
    ParkingSystem *ps = new ParkingSystem(1, 1, 0);
    vector<bool> result;
    result.push_back(ps->addCar(1));
    result.push_back(ps->addCar(2));
    result.push_back(ps->addCar(3));
    result.push_back(ps->addCar(1));
    output(result);
}
